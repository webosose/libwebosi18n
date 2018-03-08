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
 * ResBundle.h
 * @author Oleksandr Gorbunov
 */

#ifndef RESBUNDLE_H_
#define RESBUNDLE_H_

using namespace std;
#include <string>
#include <map>
#include <vector>

class ResBundle {
	public:
		/**
		 * ResBundle constructor. Creates ResBundle instance by filling translations map of localized strings loaded from
		 *  json file and specifies the target locale.
		 *
		 * @param locale specified locale in BCP 47 format that specifies target locale for client application
		 * @param file_path path to translated json file.
		 */
		ResBundle(string locale, const string file_path);
		/**
		 * ResBundle constructor. Creates ResBundle instance using next approach:
		 * specifies target locale, then specifies name of json file contains appropriate translations and path to localizable component.
		 * Then with the help of BCP47Parser class resbundle is extracting information about language, script, region and variant parts
		 * of locale and seeking for "resources" folder that might have next structure (for example let use "strings.json" file):
		 *
		 * resources /
		 * 		strings.json
		 * 		language /
		 * 			strings.json
		 * 			script /
		 * 				strings.json
		 * 				region /
		 * 					strings.json
		 * 					variant /
		 * 						strings.json
		 *
		 * 	Then resbundle instance is loading all existed json files one by one (that approach is used because of shared strings between json files,
		 * 	as each file in this list contains strings that are uniquely identifies it only.).
		 *
		 * @param locale specified locale in BCP 47 format that specifies target locale for client application
		 * @param name given name of translated json file, for example, "cppstrings.json".
		 * @param root_path path to translated json file.
		 */
		ResBundle(string locale, string name, const string root_path);
		/**
		 * ResBundle destructor. It cleans translations map before current object is to be destroyed.
		 */
		virtual ~ResBundle();

		/**
		 * Checks if resbundle object contains requested source string
		 *
		 * @param source source string to be checked on occurrence in resbundle
		 * @return true if translation was found
		 */
		virtual bool containsSource(const string& source);
		/**
		 * Returns translated string if it is in translations.
		 *
		 * @param source source string which is to be translated
		 * @return translated string if translations are found
		 */
		const string& getLocString(const string& source);
		/**
		 * Returns translated string if it is in translations.
		 *
		 * @param key key string which is a key for source string to be translated
		 *              (there should be many identical source strings with different keys)
		 * @param source source string which is to be translated
		 * @return translated string if translations are found, or source string if key was not found.
		 */
		const string& getLocString(const string& key, const string& source);
		/**
		 * Returns target locale that extracted strings could be translated into.
		 *
		 * @return locale BCP 47 format string that specifies target locale
		 */
		const string& getLocale();

		/**
		 * Splits given source string by given delimeter and returns vector of parts.
		 * @param source given source string is to be split
		 * @param delimiter separator that will be used for source string
		 */
		static vector<string> split(const string& source, const string& delimiter);

	private:
		/**
		 * Specifies BCP 47 format locale. If locale is empty default locale en-US will be used instead
		 * @param current_locale locale in BCP47 format.
		 */
		void specifyLocale(string &current_locale);
		/**
		 * Loads translations from single file
		 * @param file_path path to file that will be parsed
		 */
		void loadTranslations(string &file_path);
		/**
		 * Loads translations from all files found in target locale folder
		 * @param name files name that are same for all files.
		 * @param file_path path to component root where "resources" folder should be located.
		 */
		void loadAllTranslations(string &name, string &file_path);

	private:
		/**
		 * Pattern for json filename extension
		 */
		static const std::string jsonPattern;
		/**
		 * Target locale in BCP 47 format
		 */
		std::string locale;
		/**
		 * Container for extracted translations loaded from json file.
		 */
		std::map<std::string, std::string> translations;
};

#endif  /* RESBUNDLE_H_ */
