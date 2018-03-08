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
 * WebOSLocale.h
 * @author Oleksandr Gorbunov
 */

#ifndef WEBOSLOCALE_H_
#define WEBOSLOCALE_H_

#include <string>
using namespace std;

class WebOSLocale {
	public:
		/**
		 * Constructs a locale instance from string value;
		 * @param locale string contains locale specification in BCP 47 standard
		 */
		WebOSLocale(string locale);
		/**
		 *
		 */
		WebOSLocale(string language, string region, string script, string variant);
		/**
		 *
		 */
		string getLanguage();
		/**
		 *
		 */
		string getScript();
		/**
		 *
		 */
		string getRegion();
		/**
		 *
		 */
		string getVariant();
		/**
		 *
		 */
		string toString();
		/**
		 *
		 */
		bool isPseudo();
		/**
		 *
		 */
		bool equals(const string& locale);
		/**
		 *
		 */
		bool equals(WebOSLocale* locale);
		/**
		 *
		 */
		bool isCompatibleWith(WebOSLocale* locale);

	protected:
		/**
		 *
		 */
		void parseLocale(string &locale);

	private:
		void parseLanguage(string &item);
		void parseScript(string &item);
		void parseRegion(string &item);
		void parseVariant(string &item);

	protected:
		string language;
		string script;
		string region;
		string variant;
		static const string PSEUDO;
		static const string HYPHEN;
};

#endif /* WEBOSLOCALE_H_ */
