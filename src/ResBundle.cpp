// Copyright (c) 2013-2021 LG Electronics, Inc.
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
			pbnjson::JDomParser DOMParser(NULL);

			if (!DOMParser.parse(fileContent, inputSchema)) {
				cerr << "File " << file_path << " DOM parsing error" << endl;
				return;
			}

			pbnjson::JValue translationsJSON = DOMParser.getDom();
			if (!translationsJSON.isNull() && translationsJSON.isObject()) {

				for (pbnjson::JValue::ObjectIterator iter = translationsJSON.begin(); iter != translationsJSON.end(); iter++) {
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
		pseudo_string = "";
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

		if (source.length() > 10) {
			int length = source.length() / 5;
			for (int i = length - 1; i >= 0; i--) {
				std::ostringstream oss;
				oss << (i % 10);
				pseudo_string.append(oss.str());
			}
		}

		// Generate a 3 digit hash in base 62
		// Three digits in base 62 are 62*62*62 = 238328 numbers.
		// The largest prime less than 238328 is 238321.
		// 157291 and 238321 are both prime, so they are also co-prime with each other.
		// This means that they create an algebraic ring and multiplying by 157291
		// and truncating by 238321 will eventually hit all values from 0 to 238320
		// and distribute the hash values evenly across the range.
		{
			const string DIGITS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			long total = 1;
			for (int i = 0; i < source.length(); i++) {
				total += static_cast<int>(source.at(i));
				total *= 157291;
				total %= 238321;
			}

			long digit;
			char hash;
			digit = total % 62;
			hash = DIGITS.at((int) digit);
			pseudo_string.insert(0, 1, hash);
			total /= 62;
			digit = total % 62;
			hash = DIGITS.at((int) digit);
			pseudo_string.insert(0, 1, hash);
			total /= 62;
			hash = DIGITS.at((int) total);
			pseudo_string.insert(0, 1, hash);
		}
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

		pseudomaps[num++] = temp_pseudomap;
	}

	return pseudomaps;
}