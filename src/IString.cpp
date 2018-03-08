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
 * IString.cpp
 * Represents an international string. This type of string allows for a
 * formatting syntax very similar to the javascript ilib syntax, so that
 * strings can be shared between code in java or cpp.
 *
 * @author Oleksandr Gorbunov
 */

#include "webosi18n/cxx/IString.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <sstream>
using namespace std;

IString::IString(const string source)
{
	text = source;
}

string IString::format(map<string, string> values)
{
	string formatted = text;
	if ( !values.empty() ) {
		string keyInBraces;

		for (map<string, string>::iterator it = values.begin(); it != values.end(); ++it) {
			keyInBraces = "{" + it->first + "}";
			if (formatted.find(keyInBraces) != string::npos)
				formatted.replace(formatted.find(keyInBraces), keyInBraces.length(), it->second);
		}
	}

	return formatted;
}

string IString::format(pbnjson::JValue values)
{
	string formatted = text;

	if (!values.isNull()) {
		if (values.isObject()) {
			string keyInBraces;
			for (pbnjson::JValue::ObjectIterator iter = values.begin(); iter != values.end(); iter++) {
				keyInBraces = "{" + (*iter).first.asString() + "}";
				if (formatted.find(keyInBraces) != string::npos)
					formatted.replace(formatted.find(keyInBraces), keyInBraces.length(), (*iter).second.asString());
			}

		}
	}

	return formatted;
}

int IString::getBooleanSelector(const string& selector) {
	 if ( equalsIgnoreCase(selector,"true") ||
		 equalsIgnoreCase(selector,"yes") ||
		 equalsIgnoreCase(selector,"on") ||
		 equalsIgnoreCase(selector,"1") ) {
		 return 1;
	 } else if ( equalsIgnoreCase(selector,"false") ||
			equalsIgnoreCase(selector,"no") ||
			equalsIgnoreCase(selector,"off") ||
			equalsIgnoreCase(selector,"0") ) {
		 return 0;
	 }
	 return -1;
}

bool IString::equalsIgnoreCase(const string& source, const string& target) {
    if (source.size() != target.size()) {
        return false;
    }

    for (string::const_iterator c1 = source.begin(), c2 = target.begin(); c1 != source.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}

vector<string> IString::split(const string& source, const string& delimiter) {
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

vector<string> IString::splitBySymbol(const string& source, const char& delimiter) {
	vector<string> result;
	string line;
	stringstream  data(source);

	while(getline(data, line, delimiter))
		result.push_back(line);

	return result;
}

/*throws ParseException*/
void IString::parseChoices() {
	vector<string> choices = split(this->text, "|");
	vector<string> parts;
	string str;
	size_t i;

	strings.clear();
	selectors.clear();
	defaultChoice = "";

	for ( i = 0; i < choices.size(); i++ ) {
		parts = splitBySymbol(choices[i], '#');
		if ( parts.size() > 2 ) {
			str = choices[i].substr(choices[i].find('#') + 1);
		} else if ( parts.size() == 2 ) {
			str = parts[1];
		} else {
			// syntax error
			//throw new ParseException("syntax error in choice format pattern: " + choices[i], i);
		}

		selectors.push_back(parts[0]);
		strings.push_back(str);

		if ( parts[0].length() == 0 ) {
			defaultChoice = str;
		}
	}
}

//throws ParseException
IString* IString::getChoice(bool reference) {
	if ( text.empty() || text.length() == 0 ) {
		return NULL;
	}

	size_t i;
	IString* result = NULL;
	string selector;

	if ( strings.empty() ) {
		parseChoices();
	}

	for (i = 0; i < selectors.size(); i++) {
		selector = selectors[i];
		int value = getBooleanSelector(selector);

		if ( value == 1 ) {
			if ( reference ) {
				return new IString(strings[i]);
			}
		} else if ( value == 0 ) {
			if ( !reference ) {
				return new IString(strings[i]);
			}
		}
	}

	if (!result) {
		result = new IString(defaultChoice);
	}

	return result;
}

//throws ParseException
IString* IString::getChoice(const string& reference) {
	if ( text.empty() || text.length() == 0 ) {
		return NULL;
	}

	size_t i;
	IString* result = NULL;
	string selector;
	boost::regex xRegex;

	if ( strings.empty() ) {
		parseChoices();
	}

	if ( patterns.empty() ) {
		patterns = vector<boost::regex>();
		for (i = 0; i < selectors.size(); i++) {
			selector = selectors[i];
			if (!selector.empty() && selector.length() > 0) {
				string pattern = selector;
				boost::algorithm::to_lower(pattern);
				patterns.push_back(boost::regex(selector));
			}
		}
	}

	if (patterns.size() > 0) {
		string referenceLC = reference;
		boost::algorithm::to_lower(referenceLC);

		for ( i = 0; i < patterns.size(); i++) {
			xRegex = patterns[i];

			if (xRegex.expression()) {
				boost::smatch xMatcher;
				if (boost::regex_search(referenceLC, xMatcher, xRegex)) {
					if (xMatcher[0].compare(referenceLC) == 0)
						return new IString(strings[i]);
				}
			}

		}
	}

	if (!result) {
		result = new IString(defaultChoice);
	}

	return result;
}

//throws ParseException
IString* IString::getChoice(double reference) {
	if ( text.empty() || text.length() == 0 ) {
		return NULL;
	}

	size_t i;
	IString* result = NULL;
	double selector;
	string sel;

	if ( strings.empty() ) {
		parseChoices();
	}

	for (i = 0; i < selectors.size(); i++) {
		sel = selectors[i];
		if ( sel.length() > 2 && sel.substr (0,2) == "<=" ) {
			selector = parseDouble(sel.substr(2));
			if (reference <= selector) {
				result = new IString(strings[i]);
				i = selectors.size();
			}
		} else if ( sel.length() > 2 && sel.substr(0,2) == ">=" ) {
			selector = parseDouble(sel.substr(2));
			if (reference >= selector) {
				result = new IString(strings[i]);
				i = selectors.size();
			}
		} else if ( sel.length() > 1 && sel.at(0) == '<' ) {
			selector = parseDouble(sel.substr(1));
			if (reference < selector) {
				result = new IString(strings[i]);
				i = selectors.size();
			}
		} else if ( sel.length() > 1 && sel.at(0) == '>' ) {
			selector = parseDouble(sel.substr(1));
			if (reference > selector) {
				result = new IString(strings[i]);
				i = selectors.size();
			}
		} else if ( sel.length() > 0 ) {
			int value, dash = sel.find("-");
			if ( dash != -1 ) {
				// range
				string start = sel.substr(0, dash);
				string end = sel.substr(dash+1);
				if (reference >= parseLong(start, 10) && reference <= parseLong(end, 10)) {
					result = new IString(strings[i]);
					i = selectors.size();
				}
			} else if ( (value = getBooleanSelector(sel)) > -1 ) {
				if ( value == reference ) {
					result = new IString(strings[i]);
					i = selectors.size();
				}
			} else if ( reference == parseLong(sel, 10) ) {
				// exact amount
				result = new IString(strings[i]);
				i = selectors.size();
			}
		}
	}

	if (!result) {
		result = new IString(defaultChoice);
	}

	return result;
}

double IString::parseDouble(const string& digit_string) {
	return atof( digit_string.c_str() );
}
/**
 *
 */
long IString::parseLong(const string& digit_string, int base) {
	char * pEnd;
	return strtol(digit_string.c_str(), &pEnd, base);
}

int IString::length() {
	return text.length();
}

const string& IString::toString() {
	return text;
}

string IString::formatChoice(bool reference, map<string, string> values) {
	IString* result = getChoice(reference);
	if ( !result ) {
		return "";
	}
	string returnVal = (values.empty()) ? result->toString() : result->format(values);
	delete result;

	return returnVal;
}

string IString::formatChoice(bool reference, pbnjson::JValue values) {
	IString* result = getChoice(reference);
	if ( !result ) {
		return "";
	}
	string returnVal = (values.isNull()) ? result->toString() : result->format(values);
	delete result;

	return returnVal;
}

/*throws ParseException*/
string IString::formatChoice(double reference, map<string, string> values) {
	IString* result = getChoice(reference);
	if ( !result)
		return "";

	string returnVal = (values.empty()) ? result->toString() : result->format(values);
	delete result;

	return returnVal;
}

string IString::formatChoice(double reference, pbnjson::JValue values) {
	IString* result = getChoice(reference);
	if ( !result)
		return "";

	string returnVal = (values.isNull()) ? result->toString() : result->format(values);
	delete result;

	return returnVal;
}

string IString::formatChoice(const string& reference, map<string, string> values) {
	IString* result = getChoice(reference);
	if ( !result )
		return "";

	string returnVal = (values.empty()) ? result->toString() : result->format(values);
	delete result;

	return returnVal;
}

string IString::formatChoice(const string& reference, pbnjson::JValue values) {
	IString* result = getChoice(reference);
	if ( !result) {
		return "";
	}

	string returnVal = (values.isNull()) ? result->toString() : result->format(values);
	delete result;

	return returnVal;
}

string IString::format(const string& message, map<string, string> parameters) {
	IString* iString = new IString(message);
	string result = iString->format(parameters);
	delete iString;
    return result;
}

string IString::formatChoice(const string& message, long reference) {
	return formatChoice(message, reference, map<string, string>());
}

string IString::formatChoice(const string& message, long reference, map<string, string> parameters) {
	IString* iString = new IString(message);
	string result = iString->formatChoice(static_cast<double>(reference), parameters);
	delete iString;
	return result;
}

string IString::formatChoice(const string& message, double reference) {
	return formatChoice(message, reference, map<string, string>());
}

string IString::formatChoice(const string& message, double reference, map<string, string> parameters) {
	IString* iString = new IString(message);
	string result = iString->formatChoice(reference, parameters);
	delete iString;
	return result;
}
