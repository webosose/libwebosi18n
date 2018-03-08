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
 * WebOSLocale.cpp
 * Source file for webos locale instance
 * This is a class-helper that could parse BCP 47 format strings and provide 4 supported functional parts in BCP 47 standard:
 *   - language;
 *   - script;
 *   - region;
 *   - variant.
 * The order of above parts is not specified by standard, the only criteria - parts should be separated by dashes.
 * For each functional part usage limitations go to @see annotation.
 *
 * @author Oleksandr Gorbunov
 * @see http://en.wikipedia.org/wiki/IETF_language_tag
 * @see http://tools.ietf.org/html/bcp47
 */
#include "webosi18n/cxx/WebOSLocale.h"
#include "webosi18n/cxx/ResBundle.h"
#include <iostream>
#include <algorithm>
#include <vector>

const string WebOSLocale::PSEUDO = "zxx";
const string WebOSLocale::HYPHEN = "-";

WebOSLocale::WebOSLocale(string locale)
{
	parseLocale(locale);
}

WebOSLocale::WebOSLocale(string language, string region, string script, string variant)
{
	this->language = language;
	this->region = region;
	this->script = script;
	this->variant = variant;
}

string WebOSLocale::getLanguage()
{
	return language;
}

string WebOSLocale::getScript()
{
	return script;
}

string WebOSLocale::getRegion()
{
	return region;
}

string WebOSLocale::getVariant()
{
	return variant;
}

void WebOSLocale::parseLanguage(string &item)
{
	if (!language.empty() || item.length() < 2 || item.length() > 3) return;

	if ( find_if(item.begin(), item.end(), ::isupper) == item.end() &&
			find_if(item.begin(), item.end(), ::isdigit) == item.end())
		language = item;
}

void WebOSLocale::parseScript(string &item)
{
	if (!script.empty() || item.length() != 4) return;

	bool isValidScript = false;
	if ( isupper(*item.begin()) )
	{
		isValidScript = true;
		for (string::iterator itr = item.begin() + 1; itr != item.end(); ++itr)
		{
			if ( isupper(*itr) ) {
				isValidScript = false;
				break;
			}
		}

	}

	if (isValidScript) script = item;
}

void WebOSLocale::parseRegion(string &item)
{
	if (!region.empty() || item.length() < 2 || item.length() > 3) return;

	if (item.length() == 2)
	{
		if ( (find_if(item.begin(), item.end(), ::islower) == item.end()) )
				region = item;
	}
	else
	{
		if ( !(find_if(item.begin(), item.end(), ::isdigit) == item.end()) )
			region = item;
	}
}

void WebOSLocale::parseVariant(string &item)
{
	if ( item == script || item.length() < 5 || item.length() > 8) return;
	if (find_if(item.begin(), item.end(), ::isdigit) == item.end())
	{
		if (variant.empty())
			variant = item;
		else
			variant += HYPHEN + item;
	}
}

void WebOSLocale::parseLocale(string &locale)
{
	vector<string> locale_parts = ResBundle::split(locale, HYPHEN);
	for (vector<string>::iterator itr = locale_parts.begin(); itr != locale_parts.end(); ++itr)
	{
		parseLanguage(*itr);
		parseScript(*itr);
		parseRegion(*itr);
		parseVariant(*itr);
	}
}

bool WebOSLocale::isPseudo()
{
	return (language.compare(PSEUDO) == 0) ? true : false;
}

string WebOSLocale::toString()
{
	string result = "";
	if ( language.length() > 0 ) {
		result.append(language);
	}
	if ( script.length() > 0 ) {
		if ( result.length() > 0 ) {
			result.append(HYPHEN);
		}
		result.append(script);
	}
	if ( region.length() > 0 ) {
		if ( result.length() > 0 ) {
			result.append(HYPHEN);
		}
		result.append(region);
	}
	if ( variant.length() > 0 ) {
		if ( result.length() > 0 ) {
			result.append(HYPHEN);
		}
		result.append(variant);
	}

	return result;
}


bool WebOSLocale::equals(const string& locale)
{
	if ( toString().compare(locale) == 0 ) {
		return true;
	}
	return false;
}

bool WebOSLocale::equals(WebOSLocale* locale)
{
	if (!locale) return false;
	bool result = (this->language.compare(locale->language) == 0 &&
			this->script.compare(locale->script) == 0 &&
			this->region.compare(locale->region) == 0 &&
			this->variant.compare(locale->variant) == 0 );
	return result;

}

bool WebOSLocale::isCompatibleWith(WebOSLocale* locale)
{
	if (!locale) return false;
	return true;
}

/*

public String toString()
{
	StringBuilder ret = new StringBuilder();
	if ( language != null && language.length() > 0 ) {
		ret.append(language);
	}
	
	if ( script != null && script.length() > 0 ) {
		if ( ret.length() > 0 ) {
			ret.append("-");
		}
		ret.append(script);
	}

	if ( region != null && region.length() > 0 ) {
		if ( ret.length() > 0 ) {
			ret.append("-");
		}
		ret.append(region);
	}

	if ( variant != null && variant.length() > 0 ) {
		if ( ret.length() > 0 ) {
			ret.append("-");
		}
		ret.append(variant);
	}

	return ret.toString();
}*/
