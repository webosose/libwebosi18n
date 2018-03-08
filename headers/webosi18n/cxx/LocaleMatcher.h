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
 * ScriptInfo.h
 * @author Oleksandr Gorbunov
 */

#ifndef LOCALE_MATCHER_H_
#define LOCALE_MATCHER_H_

#include <string>
#include <map>
using namespace std;

class LocaleMatcher {
	public:
		/**
		 * Seeks for full locale name in locales map and returns script of target locale,
		 * otherwise - default script Latn
		 * @param target locale in BCP 47 format
		 * @return native script for given locale and default script Latn if locale is not detected
		 */
		static string getScriptByLocale(const string& locale);

	protected:
		/**
		 * static initialization of locales container
		 */
		static map<string, string> initLocales();
		/**
		 * Trying to extract script from target locale by given kay and store it to script param
		 * passed as reference
		 * @param key key to be seeking to match locale that contains native script
		 * @param script reference that should be modified with current script value if it would
		 * be extracted
		 */
		static void extractScript(const string& key, string& script);

	protected:
		static map<string, string> locales;
		static const string DEFAULT_SCRIPT;
		static const string DASH;
		static const string LOCALESJSON_PATH;
};

#endif /* LOCALE_MATCHER_H_ */
