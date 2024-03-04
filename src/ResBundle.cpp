// Copyright (c) 2013-2023 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

/*
 * ResBundle.cpp
 * Source file for loading json files and extracting values
 *
 * @author Oleksandr Gorbunov
 *
 */
#include "webosi18n/cxx/ResBundle.h"
#include "webosi18n/cxx/WebOSLocale.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <pbnjson.hpp>
#include <sys/stat.h>
#include <list>
#include <cmath>

const string ResBundle::jsonPattern = ".json";

ResBundle::ResBundle(string current_locale, string file_path)
{
	specifyLocale(current_locale);
	try {
		loadTranslations(file_path);
	} catch (exception& exception) {
		cerr << "Invalid filename: " << exception.what() << endl;
	}
}

ResBundle::ResBundle(string current_locale, string name, string root_path)
{
	specifyLocale(current_locale);
	try {
		loadAllTranslations(name, root_path);
	} catch (exception& exception) {
		cerr << "Invalid filename: " << exception.what() << endl;
	}
}

ResBundle::~ResBundle()
{
	translations.clear();
	pseudomap.clear();
}

bool ResBundle::isPseudoLocale(string &current_locale)
{
	WebOSLocale* webOSLocale = new WebOSLocale(current_locale);

	bool isPseudo = webOSLocale->isPseudo();
	delete webOSLocale;

	return isPseudo;
}

void ResBundle::specifyLocale(string &current_locale)
{
	if (current_locale.empty()) {
		current_locale = "en-US";
	}
	locale = current_locale;
}

void ResBundle::loadAllTranslations(string &file_name, string &file_path)
{
	if (isPseudoLocale(locale)) {
		pseudomap = initPseudoCharMap();
		return;
	}

	if (mismatch( jsonPattern.rbegin(), jsonPattern.rend(), file_name.rbegin()).first != jsonPattern.rend() )
			throw invalid_argument("File " + file_name + " has another extension instead of plain JSON extension.");

	WebOSLocale* webOSLocale = new WebOSLocale(locale);
	string language = webOSLocale->getLanguage();
	string script = webOSLocale->getScript();
	string region = webOSLocale->getRegion();
	string variant = webOSLocale->getVariant();
	delete webOSLocale;

	{
		vector<string> loc_files;
		string resources_path = file_path + "/resources", tmp_path = "";
		loc_files.push_back(resources_path + "/" + file_name);

		if (!language.empty()) {
			tmp_path = resources_path + "/" + language + "/";
			loc_files.push_back(tmp_path + file_name);
		}
		if (!region.empty()) {
			tmp_path = resources_path + "/und/" + region + "/";
			loc_files.push_back(tmp_path + file_name);
		}
		if (!language.empty()) {
			if (!script.empty()) {
				tmp_path = resources_path + "/" + language + "/" + script + "/";
				loc_files.push_back(tmp_path + file_name);
			}
			if (!region.empty()) {
				tmp_path = resources_path + "/" + language + "/" + region + "/";
				loc_files.push_back(tmp_path + file_name);
			}
		}
		if (!region.empty() && !variant.empty()) {
			tmp_path = resources_path + "/und/" + region + "/" + variant + "/";
			loc_files.push_back(tmp_path + file_name);
		}
		if (!language.empty() && !script.empty() && !region.empty()) {
			tmp_path = resources_path + "/" + language + "/" + script + "/" + region + "/";
			loc_files.push_back(tmp_path + file_name);
		}
		if (!language.empty() && !region.empty() && !variant.empty()) {
			tmp_path = resources_path + "/" + language + "/" + region + "/" + variant + "/";
			loc_files.push_back(tmp_path + file_name);
		}
		if (!language.empty() && !script.empty() && !region.empty()) {
			tmp_path = resources_path + "/" + language + "/" + script + "/" + region + "/" + variant + "/";
			loc_files.push_back(tmp_path + file_name);
		}

		for (vector<string>::iterator it = loc_files.begin() ; it != loc_files.end(); ++it) {
			 loadTranslations(*it);
		}

		loc_files.clear();
	}
}

void ResBundle::loadTranslations(string &file_path)
{
	if (isPseudoLocale(locale)) {
		pseudomap = initPseudoCharMap();
		return;
	}

	ifstream in (file_path.c_str(), ifstream::in);
	if (in)
	{
		stringstream stringbuffer;
		stringbuffer << in.rdbuf();
		string fileContent = stringbuffer.str();

		if (!fileContent.empty()) {
			pbnjson::JSchemaFragment inputSchema("{}");
			pbnjson::JDomParser DOMParser;

			if (!DOMParser.parse(fileContent, inputSchema)) {
				cerr << "File " << file_path << " DOM parsing error" << endl;
				return;
			}

			pbnjson::JValue translationsJSON = DOMParser.getDom();
			if (!translationsJSON.isNull() && translationsJSON.isObject()) {
				for (pbnjson::JValue::ObjectIterator iter = translationsJSON.children().begin(); iter != translationsJSON.children().end(); iter++) {
					translations[(*iter).first.asString()] = (*iter).second.asString();
				}
			}
		}
	}
}

bool ResBundle::containsSource(const string& source)
{
	if( translations.find(source) != translations.end() )
		return true;

	return false;
}

const string& ResBundle::getLocString(const string& source)
{
	return getLocString(source, source);
}

const string& ResBundle::getLocString(const string& key, const string& source)
{
	if (isPseudoLocale(locale)) {
		return getPseudoString(key, source);
	} else {
		map<string, string>::iterator it = translations.find(key);
		if (it != translations.end()) {
			return it->second;
		}
		return source;
	}
}

const string& ResBundle::getPseudoString(const string& key, const string& source)
{
	static string pseudo_string("ÃßÇ " + source + " ŴŶŻ");

	int map_size = pseudomap.size();
	if (map_size > 0) {
		pseudo_string = "["; // for encapsulation
		for (int i = 0; i < source.length(); i++) {
			int idx = (map_size > 1) ? i % map_size : 0;

			map<string,string>::iterator it;
			string temp;
			temp.push_back(source.at(i));

			it = pseudomap[idx].find(temp);

			if (it != pseudomap[idx].end()) {
				pseudo_string += it->second;
			} else {
				pseudo_string += temp;
			}
		}

		int addLen = 0;
		if (source.length() <= 20) {
			addLen = round(source.length() / 2);
		} else if (source.length() > 20 && source.length() <= 40) {
			addLen = round(source.length() / 3);
		} else {
			addLen = round(source.length() / 5);
		}

		if (addLen > 0) {
			for (int i = addLen - 1; i >= 0; i--) {
				std::ostringstream oss;
				oss << (i % 10);
				pseudo_string.append(oss.str());
			}
		}

		pseudo_string += "]"; // for encapsulation
	}

	return pseudo_string;
}

const string& ResBundle::getLocale()
{
	return locale;
}

vector<string> ResBundle::split(const string& source, const string& delimiter) {
	vector<string> result;

	if (delimiter.empty()) {
		result.push_back(source);
		return result;
	}
	string::const_iterator tempStart = source.begin(), tempEnd;
	while (true) {
		tempEnd = search(tempStart, source.end(), delimiter.begin(), delimiter.end());

		string tempSource(tempStart, tempEnd);

		if ( !tempSource.empty() ) {
			tempSource.erase(remove( tempSource.begin(), tempSource.end(), '\"' ),  tempSource.end());
			if (tempSource.at( tempSource.length() - 1 ) == ',')
				tempSource = tempSource.substr(0, tempSource.size() - 1);
			result.push_back(tempSource);
		}

		if ( tempEnd == source.end() ) break;

		tempStart = tempEnd + delimiter.size();
	}
	return result;
}

map< int, map<string, string> > ResBundle::initPseudoCharMap() {
	string temp_json_path = PATH_TO_JSON;
	WebOSLocale* webOSLocale = new WebOSLocale(locale);
	string language = webOSLocale->getLanguage();
	string script = webOSLocale->getScript();
	delete webOSLocale;

	std::list<string> files;
	if (script.compare("Hans") == 0) {
		files.push_back(temp_json_path + "/pseudomap.json");
		files.push_back(temp_json_path + "/zxx/Cyrl/pseudomap.json");
		files.push_back(temp_json_path + "/zxx/Hebr/pseudomap.json");
		files.push_back(temp_json_path + "/zxx/Hans/pseudomap.json");
	} else if (script.compare("Cyrl") == 0 || script.compare("Hebr") == 0) {
		files.push_back(temp_json_path + "/" + language + "/" + script + "/pseudomap.json");
	} else {
		files.push_back(temp_json_path + "/pseudomap.json");
	}

	map< int, map<string, string> > pseudomaps = map< int, map<string, string> >();
	int num = 0;
	list<string>::iterator li;

	for (li=files.begin(); li!=files.end(); li++) {
		temp_json_path = *li;

		ifstream in(temp_json_path.c_str(), fstream::in);
		map<string, string> temp_pseudomap = map<string, string>();

		if (in) {
			stringstream buffer;
			buffer << in.rdbuf();
			string result = buffer.str();

			if (!result.empty()) {
				pbnjson::JSchemaFragment inputSchema("{}");
				pbnjson::JDomParser DOMParser;

				if (!DOMParser.parse(result, inputSchema)) {
					cerr << "File " << temp_json_path << " parsing error" << endl;
					return pseudomaps;
				}

				pbnjson::JValue pseudomap = DOMParser.getDom();
				for (pbnjson::JValue::ObjectIterator iter = pseudomap.children().begin(); iter != pseudomap.children().end(); iter++) {
					if (((*iter).second).isString()) {
						temp_pseudomap.insert( pair<string, string>((*iter).first.asString(), (*iter).second.asString()) );
					}
				}
			}
		}

		pseudomaps[num++] = std::move(temp_pseudomap);
	}

	return pseudomaps;
}