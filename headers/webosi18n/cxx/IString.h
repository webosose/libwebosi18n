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
 * IString.h
 * @author Oleksandr Gorbunov
 *
 */

#ifndef ISTRING_H_
#define ISTRING_H_

#include <string>
#include <map>
#include <vector>
#include <boost/regex.hpp>
#include <pbnjson.hpp>
using namespace std;

class IString {
	public:
		/**
		 * IString constructor. Creates new IString instance with the given text.
		 * @param text the text to wrap
		 */
		IString(const string source);
		/**
		 * Format a string with the given named values.
		 *
		 * The string can contain any text that a regular Java string can
		 * contain. Replacement parameters have the syntax:
		 *
		 * <pre>
		 * {name}
		 * </pre>
		 *
		 * Where "name" can be any string surrounded by curly brackets. The value of
		 * "name" is taken from the values argument.<p>
		 *
		 * Example:
		 *
		 * <pre>
		 * int num_objects = 12;
		 * IString* str = new IString("There are {num} objects.");
		 * std::map<std::string,std::string> values = std::map<std::string,std::string>();
		 * values.insert ( std::pair<std::string, std::string> ("num", "12") );
		 * System.out.println(str.format(values));
		 * std::cout << str->format(values) << std::endl;
		 * </pre>
		 *
		 * Would give the output:
		 *
		 * <pre>
		 * There are 12 objects.
		 * </pre>
		 *
		 * If a property is missing from the value map, the replacement
		 * parameter substring is left untouched in the string, and a different
		 * set of parameters may be applied a second time. This way, different
		 * parts of the code may format different parts of the message that they
		 * happen to know about.<p>
		 *
		 * Example:
		 *
		 * <pre>
		 * int num_objects = 12;
		 * IString* str = new IString("There are {num} objects in the {container}.");
		 * std::map<std::string,std::string> values = std::map<std::string,std::string>();
		 * std::stringstream ss;
		 * ss << num_objects;
		 * values.insert ( std::pair<std::string, std::string> ("num", ss.str()) );
		 * System.out.println(str.format(values));
		 * std::cout << str->format(values) << std::endl;
		 * </pre>
		 *
		 * Would give the output:<p>
		 *
		 * <pre>
		 * There are 12 objects in the {container}.
		 * </pre>
		 *
		 * The result can then be formatted again with a different value map that
		 * specifies a value for the "container" property.
		 *
		 * @param values a set of named values
		 * @return the string with as many replacement parameters
		 * replaced with named values as possible
		 */
		string format(map<string,string> values);
		/**
		 * This is the same as {@link IString#format(map<string,string>)} except the replacement
		 * values come from a JSON object instead of a map.
		 *
		 * @param values a set of named values in a JSON object
		 * @return the string with as many replacement parameters
		 * replaced with named values as possible
		 */
		string format(pbnjson::JValue values);
		/**
		 * Format a string as one of a choice of strings dependent on the value of
		 * a particular reference argument.<p>
		 *
		 * The syntax of the choice string is as follows. The string contains a
		 * series of choices separated by a vertical bar character "|". Each choice
		 * has a selector, which is a value or range of values to match and an optional
		 * operator, followed by a hash character "#", followed by the string to use if
		 * the reference argument matches the criteria.<p>
		 *
		 * Example string:
		 *
		 * <pre>
		 * int num_objects = 2;
		 * IString* str = new IString("0#There are no objects.|1#There is one object.|2#There are {number} objects.");
		 * std::map<std::string,std::string> values = std::map<std::string,std::string>();
		 * std::stringstream ss;
		 * ss << num_objects;
		 * values.insert ( std::pair<std::string, std::string> ("number", ss.str()) );
		 * System.out.println(str.format(values));
		 * std::cout << str->formatChoice(num_objects, values) << std::endl;
		 * </pre>
		 *
		 * Gives the output:
		 *
		 * <pre>
		 * "There are 2 objects."
		 * </pre>
		 *
		 * The strings to format may contain replacement variables that will be formatted
		 * using the {@link IString#format(map<string,string>)} method and the values argument as a source of values
		 * to use while formatting those variables.<p>
		 *
		 * If the selector for a particular choice is empty, that choice will be used
		 * as the default one for use when none of the other choice's criteria match.<p>
		 *
		 * Example string:
		 *
		 * <pre>
		 *  int num_objects = 22;
		 * IString* str = new IString("0#There are no objects.|1#There is one object.|#There are {number} objects.");
		 * std::map<std::string,std::string> values = std::map<std::string,std::string>();
		 * std::stringstream ss;
		 * ss << num_objects;
		 * values.insert ( std::pair<std::string, std::string> ("number", ss.str()) );
		 * System.out.println(str.format(values));
		 * std::cout << str->formatChoice(num_objects, values) << std::endl;
		 * </pre>
		 *
		 * Gives the output:
		 *
		 * <pre>
		 * "There are 22 objects."
		 * </pre>
		 *
		 * If multiple selectors can match a given reference argument, the first one
		 * encountered in the string will be used. If no selectors match the
		 * reference argument, then the default choice will be used. If there is no default
		 * choice defined, then this method will return an empty string.<p>
		 *
		 * <b>Special Syntax</b><p>
		 *
		 * For any choice format string, all of the selectors in the string should be of
		 * the same type. The available types are: numeric, boolean, or string/regexp. The type
		 * of the selectors is determined by the type of the reference argument.<p>
		 *
		 * If the reference argument is numeric, then some special operator syntax can be used
		 * in the selectors to match numeric ranges.<p>
		 *
		 * <ul>
		 * <li><i>&gt;x</i> - match any number that is greater than x
		 * <li><i>&gt;=x</i> - match any number that is greater than or equal to x
		 * <li><i>&lt;x</i> - match any number that is less than x
		 * <li><i>&lt;=x</i> - match any number that is less than or equal to x
		 * <li><i>start-end</i> - match any number in the range [start,end)
		 * </ul>
		 *
		 * If the type of the reference argument is boolean, the strings "true", "on", "yes", "1", or
		 * "false", "off", "no", or "0" (without the quotes) may appear as the selectors.<p>
		 *
		 * If the type of the reference argument is string, then the selectors may contain
		 * regular expressions, or just regular strings as if they were degenerate regexps.
		 *
		 * @param reference The reference value used to select the choice to use in the choice array
		 * @param values The map of parameter values that replace the replacement
		 * variables in the string
		 * @return the formatted string
		 */
		string formatChoice(double reference, map<string, string> values);
		/**
		 * This is the same as {@link IString#formatChoice(double, map<string,string>)} except that the
		 * named replacement values come from a JSON object instead of a map.
		 *
		 * @see IString#formatChoice(double, map<string,string>)
		 * @param reference The reference value used to select the choice to use in the choice array
		 * @param values The JSON object containing parameter values that replace the
		 * replacement variables in the string
		 * @return the formatted string
		 */
		string formatChoice(double reference, pbnjson::JValue values);
		/**
		 * This is the same as {@link IString#formatChoice(double, map<string,string>)}
		 * except that the type of the reference argument is boolean. In this case, the
		 * strings "true", "on", "yes", "1", or "false", "off", "no", or "0" (without the
		 * quotes) may appear as the selectors. If a choice string with boolean selectors is
		 * formatted with a numeric argument index instead, then the value of "false" is
		 * taken to be 0, and the value of true is taken to be 1.
		 *
		 * @see IString#formatChoice(double, map<string,string>)
		 * @param reference The reference value used to select the choice to use in the choice array
		 * @param values The map of parameter values that replace the replacement
		 * variables in the string
		 * @return the formatted string
		 */
		string formatChoice(bool reference, map<string, string> values);
		/**
		 * This is the same as {@link IString#formatChoice(boolean, map<string,string>)} except that the
		 * named replacement values come from a JSON object instead of a map.
		 *
		 * @see IString#formatChoice(double, map<string,string>)
		 * @param reference The reference value used to select the choice to use in the choice array
		 * @param values The JSON object containing parameter values that replace the
		 * replacement variables in the string
		 * @return the formatted string
		 */
		string formatChoice(bool reference, pbnjson::JValue values);
		/**
		 * This is the same as {@link IString#formatChoice(double, map<string,string>)}
		 * except that the type of the reference argument is a string which is matched
		 * against the regular expressions selectors in the choice string.
		 * A choice is selected if the regular expression
		 * matches the reference argument. The first choice that has its regexp match
		 * the reference argument is the one that is selected. Remember to escape
		 * any "#" or "|" characters in the regular expression so that they do not
		 * conflict with the syntax of the choice format string.
		 *
		 * @see IString#formatChoice(double, map<string,string>)
		 * @param reference The reference value used to select the choice to use in the choice array
		 * @param values The map of parameter values that replace the replacement
		 * variables in the string
		 * @return the formatted string
		 */
		string formatChoice(const string& reference, map<string, string> values);
		/**
		 * This is the same as {@link IString#formatChoice(string, map<string,string>)} except that the
		 * named replacement values come from a JSON object instead of a map.
		 *
		 * @see IString#formatChoice(double, map<string,string>)
		 * @param reference The reference value used to select the choice to use in the choice array
		 * @param values The JSON object containing parameter values that replace the
		 * replacement variables in the string
		 * @return the formatted string
		 */
		string formatChoice(const string& reference, pbnjson::JValue values);
		/**
		 * Return the length of the given string in characters.
		 * @return the length of the given string in characters
		 */
		int length();
		/**
		 * Returns the string value of the given text.
		 * @return string value of text field
		 */
		const string& toString();
		/**
		 * Static convenience method to format without an IString instance.
		 *
		 * @param message string to format
		 * @param parameters parameters to format into the string
		 * @return a formatted string
		 */
		static string format(const string& message, map<string, string> parameters);
		/**
		 * Static convenience method to format choices without an IString instance.
		 *
		 * @param message string to format
		 * @param reference reference value
		 * @return a formatted string
		 * @throws ParseException if the syntax of the choice format is wrong
		 */
		static string formatChoice(const string& message, long reference);
		/**
		 * Static convenience method to format choices without an IString instance.
		 *
		 * @param message string to format
		 * @param reference reference value
		 * @param parameters parameters to format into the string
		 * @return a formatted string
		 * @throws ParseException if the syntax of the choice format is wrong
		 */
		static string formatChoice(const string& message, long reference, map<string, string> parameters);
		/**
		 * Static convenience method to format choices without an IString instance.
		 *
		 * @param message string to format
		 * @param reference reference value
		 * @return a formatted string
		 * @throws ParseException if the syntax of the choice format is wrong
		 */
		static string formatChoice(const string& message, double reference);
		/**
		 * Static convenience method to format choices without an IString instance.
		 *
		 * @param message string to format
		 * @param reference reference value
		 * @param parameters parameters to format into the string
		 * @return a formatted string
		 * @throws ParseException if the syntax of the choice format is wrong
		 */
		static string formatChoice(const string& message, double reference, map<string, string> parameters);

	protected:
		/**
		 * Compares two given strings in case-insensitive way
		 * @return true if two given strings are equal not considering about case-sensitivity
		 */
		bool equalsIgnoreCase(const string& source, const string& target);
		/**
		 * Converts possible string expressions to integer value,
		 * true, yes, on ,1 --> 1;
		 * false, no, off, 0 ---> 0.
		 */
		int getBooleanSelector(const string& selector);
		IString* getChoice(bool reference);
		IString* getChoice(const string& reference);
		IString* getChoice(double reference);
		/**
		 * Parses all of the available choices and fills selectors and strings containers.
		 */
		void parseChoices();

	private:
		/**
		 * Parses digit sting to return a double value.
		 * @return double value from difit string
		 */
		double parseDouble(const string& digit_string);
		/**
		 * Parses digit sting to return a long value.
		 * @return long value from difit string
		 */
		long parseLong(const string& digit_string, int base);
		/**
		 * Splits given source string by given delimeter and returns vector of parts.
		 * @param source given source string is to be split
		 * @param delimiter separator that will be used for source string
		 */
		static vector<string> split(const string& source, const string& delimiter);
		/**
		 * Splits given source string by specifiec delimeter and returns vector of parts.
		 * @param source given source string is to be split
		 * @param delimiter char separator that will be used for source string
		 */
		static vector<string> splitBySymbol(const string& source, const char& delimiter);

	protected:
		string text;
		vector<string> selectors;
		vector<string> strings;
		string defaultChoice;
		vector<boost::regex> patterns;
};

#endif /* ISTRING_H_ */
