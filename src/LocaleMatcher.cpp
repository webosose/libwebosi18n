// Copyright (c) 2013-2018 LG Electronics, Inc.
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
 * ScriptInfo.cpp
 * @author Oleksandr Gorbunov
 */

#include "webosi18n/cxx/LocaleMatcher.h"
#include "webosi18n/cxx/WebOSLocale.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <pbnjson.hpp>
using namespace std;

const string LocaleMatcher::DEFAULT_SCRIPT = "Latn";
const string LocaleMatcher::DASH = "-";
const string LocaleMatcher::LOCALESJSON_PATH = "data/locale/likelylocales.json";
map<string, string> LocaleMatcher::locales = initLocales();

map<string, string> LocaleMatcher::initLocales() {
	ifstream in(LOCALESJSON_PATH.c_str(), fstream::in);
	map<string,string> temp_locales = map<string,string>();

	if (in) {
		stringstream buffer;
		buffer << in.rdbuf();
		string result = buffer.str();

		if (!result.empty()) {
			pbnjson::JSchemaFragment inputSchema("{}");
			pbnjson::JDomParser DOMParser(NULL);

			if (!DOMParser.parse(result, inputSchema)) {
				cerr << "File " << LOCALESJSON_PATH << " parsing error" << endl;
				return temp_locales;
			}

			pbnjson::JValue localesJSON = DOMParser.getDom();
			for (pbnjson::JValue::ObjectIterator iter = localesJSON.begin(); iter != localesJSON.end(); iter++) {
				if (((*iter).second).isString()) {
					temp_locales.insert( pair<string, string>((*iter).first.asString(), (*iter).second.asString()) );
				}

			}
		}
	}

	return temp_locales;
}

string LocaleMatcher::getScriptByLocale(const string& locale) {
	string target_script = DEFAULT_SCRIPT;

	if ( !locales.empty() ) {
		WebOSLocale* target = new WebOSLocale(locale);
		const string language = target->getLanguage();
		const string region = target->getRegion();
		const string langRegion = target->getLanguage().append(DASH).append(target->getRegion());
		delete target;

		if( locales.find(language) != locales.end() ) {
			extractScript(language, target_script);
		} else if( locales.find(region) != locales.end() ) {
			extractScript(language, target_script);
		} else if( locales.find(language) != locales.end() ) {
			extractScript(language, target_script);
		}

	}

	return target_script;
}

void LocaleMatcher::extractScript(const string& key, string& script) {
	map<string, string>::iterator it = locales.find(key);
	if (it != locales.end()) {
		WebOSLocale* extractedLocale = new WebOSLocale( it->second );
		script = extractedLocale->getScript();
		delete extractedLocale;
	}
}
