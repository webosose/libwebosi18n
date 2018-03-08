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
 * IString_test.cpp
 *
 * @author Oleksandr Gorbunov
 */

#include "webosi18n/cxx/IString.h"
#include "TestIString.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <iostream>

/*
 * Simple C++ Test Suite for IString
 */

size_t iStringTestFailures = 0;

bool assertNotNull(IString* str, string message) {
	if (!str) {
		cout << "\n%TEST_FAILED% testname = " + message + " TestIString message=error" << endl;
		++iStringTestFailures;
		return true;
	}
	return false;
}

string intToString(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

void compareResult(string expected, string result, string method_name) {
	if (expected.compare(result) != 0) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestIString message=error" << endl;
		cout << "				expected: " << expected << ", actual: " << result << endl;
		++iStringTestFailures;
	}
}

void testStringConstructorFull() {
	IString* str = new IString("test test test");

	if (assertNotNull(str, "testStringConstructorFull")) return;

	int expected_length = 14;
	if (expected_length != str->length()) {
		cout << "\n%TEST_FAILED% testname = testStringConstructorFull TestIString message=error" << endl;
		++iStringTestFailures;
	} else {
		string expected = "test test test";
		compareResult(expected, str->toString(), "testStringConstructorFull");
	}

	delete str;
}

void testStringFormatNoArgs() {
	string source = "Format this string.";
	IString* str = new IString(source);

	if (assertNotNull(str, "testStringFormatNoArgs")) return;

	string current_result = str->format(map<string, string>());
	compareResult(source, str->toString(), "testStringFormatNoArgs");
	delete str;
}

void testStringFormatEmpty() {
	string source = "";
	IString* str = new IString(source);

	if (assertNotNull(str, "testStringFormatEmpty")) return;

	compareResult(source, str->toString(), "testStringFormatEmpty");
	delete str;
}

void testStringFormatEmptyWithArgs() {
	IString* str = new IString("");

	if (assertNotNull(str, "testStringFormatEmptyWithArgs")) return;

	map<string, string> values = map<string, string>();
	values.insert ( pair<string, string> ("test", "Foo") );
	string expected = "";

	compareResult(expected, str->format(values), "testStringFormatEmptyWithArgs");
	delete str;
}

void testStringFormatWithArg() {
	string source = "Format {size} string.";
	IString* str = new IString(source);

	if (assertNotNull(str, "testStringFormatWithArg")) return;

	map<string, string> values;
	values.insert ( pair<string, string> ("size", "medium") );

	string expected = "Format medium string.";
	compareResult(expected, str->format(values), "testStringFormatWithArg");
	delete str;
}

void testStringFormatWithMultipleArgs() {
	IString* str = new IString("Format {size} {object}.");

	if (assertNotNull(str, "testStringFormatWithMultipleArgs")) return;

	map<string, string> values;
	values.insert ( pair<string, string> ("size", "medium") );
	values.insert ( pair<string, string> ("object", "string") );

	string expected = "Format medium string.";
	compareResult(expected, str->format(values), "testStringFormatWithMultipleArgs");
	delete str;
}

void testStringFormatWithMissingArgs() {
	IString* str = new IString("Format {size} {object}.");

	if (assertNotNull(str, "testStringFormatWithMissingArgs")) return;

	map<string, string> values;
	values.insert ( pair<string, string> ("object", "string") );

	string expected = "Format {size} string.";
	compareResult(expected, str->format(values), "testStringFormatWithMissingArgs");
	delete str;
}

void testStringFormatWithEmptyArg() {
	IString* str = new IString("Format {size} string.");

	if (assertNotNull(str, "testStringFormatWithEmptyArg")) return;

	map<string, string> values;
	values.insert ( pair<string, string> ("size", "") );

	string expected = "Format  string.";
	compareResult(expected, str->format(values), "testStringFormatWithEmptyArg");
	delete str;
}

void testStringFormatHandleNonAsciiParam() {
	IString* str = new IString("Format {size} string.");

	if (assertNotNull(str, "testStringFormatHandleNonAsciiParam")) return;

	map<string, string> values;
	values.insert ( pair<string, string> ("size", "médïûm") );

	string expected = "Format médïûm string.";
	compareResult(expected, str->format(values), "testStringFormatHandleNonAsciiParam");
	delete str;
}

void testStringFormatHandleNonAsciiReplacement() {
	IString* str = new IString("Format {sïzé} string.");

	if (assertNotNull(str, "testStringFormatHandleNonAsciiReplacement")) return;

	map<string, string> values;
	values.insert ( pair<string, string> ("sïzé", "medium") );

	string expected = "Format medium string.";
	compareResult(expected, str->format(values), "testStringFormatHandleNonAsciiReplacement");
	delete str;
}

void testStringFormatWithArgJSON() {
	IString* str = new IString("Format {size} string.");

	if (assertNotNull(str, "testStringFormatWithArgJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("size", "medium");

	string expected = "Format medium string.";
	compareResult(expected, str->format(json), "testStringFormatWithArgJSON");
	delete str;
}

void testStringFormatWithMultipleArgsJSON() {
	IString* str = new IString("Format {size} {object}.");

	if (assertNotNull(str, "testStringFormatWithMultipleArgsJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("size", "medium");
	json.put("object", "string");

	string expected = "Format medium string.";
	compareResult(expected, str->format(json), "testStringFormatWithMultipleArgsJSON");
	delete str;
}

void testStringFormatWithMissingArgsJSON() {
	IString* str = new IString("Format {size} {object}.");

	if (assertNotNull(str, "testStringFormatWithMissingArgsJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("object", "string");

	string expected = "Format {size} string.";
	compareResult(expected, str->format(json), "testStringFormatWithMissingArgsJSON");
	delete str;
 }

void testStringFormatWithEmptyArgJSON() {
	IString* str = new IString("Format {size} string.");

	if (assertNotNull(str, "testStringFormatWithEmptyArgJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("size", "");

	string expected = "Format  string.";
	compareResult(expected, str->format(json), "testStringFormatWithEmptyArgJSON");
	delete str;
}

void testStringFormatHandleNonAsciiParamJSON() {
	IString* str = new IString("Format {size} string.");

	if (assertNotNull(str, "testStringFormatHandleNonAsciiParamJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("size", "médïûm");

	string expected = "Format médïûm string.";
	compareResult(expected, str->format(json), "testStringFormatHandleNonAsciiParamJSON");
	delete str;
}

void testStringFormatHandleNonAsciiReplacementJSON() {
	IString* str = new IString("Format {sïzé} string.");

	if (assertNotNull(str, "testStringFormatHandleNonAsciiReplacementJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("sïzé", "medium");

	string expected = "Format medium string.";
	compareResult(expected, str->format(json), "testStringFormatHandleNonAsciiReplacementJSON");
	delete str;
}

void testStringFormatMultipleReplacementsJSON() {
	IString* str = new IString("User {user} has {num} objects in their {container}.");

	if (assertNotNull(str, "testStringFormatMultipleReplacementsJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("user", "edwin");
	json.put("num", "2");
	json.put("container", "locker");

	string expected = "User edwin has 2 objects in their locker.";
	compareResult(expected, str->format(json), "testStringFormatMultipleReplacementsJSON");
	delete str;
}

void testStringFormatChoiceSimple1() {
	IString* str = new IString("1#first string|2#second string");

	if (assertNotNull(str, "testStringFormatChoiceSimple1")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(1.0, map<string, string>() ), "testStringFormatChoiceSimple1");
	delete str;
}

void testStringFormatChoiceSimple2() {
	IString* str = new IString("1#first string|2#second string");

	if (assertNotNull(str, "testStringFormatChoiceSimple2")) return;

	string expected = "second string";
	compareResult(expected, str->formatChoice(2.0, map<string, string>()), "testStringFormatChoiceSimple2");
	delete str;
}

void testStringFormatChoiceOnlyOneChoicePositive() {
	IString* str = new IString("1#first string");

	if (assertNotNull(str, "testStringFormatChoiceOnlyOneChoicePositive")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(1.0, map<string, string>()), "testStringFormatChoiceOnlyOneChoicePositive");
	delete str;
}

void testStringFormatChoiceOnlyOneChoiceNegative() {
	IString* str = new IString("1#first string");

	if (assertNotNull(str, "testStringFormatChoiceOnlyOneChoiceNegative")) return;

	string expected = "";
	compareResult(expected, str->formatChoice(2.0, map<string, string>()), "testStringFormatChoiceOnlyOneChoiceNegative");
	delete str;
}

void testStringFormatChoiceNoString() {
	IString* str = new IString("");

	if (assertNotNull(str, "testStringFormatChoiceNoString")) return;

	string expected = "";
	compareResult(expected, str->formatChoice(2.0, map<string, string>()), "testStringFormatChoiceNoString");
	delete str;
}

void testStringFormatChoiceSimpleNoMatch() {
	IString* str = new IString("1#first string|2#second string");

	if (assertNotNull(str, "testStringFormatChoiceSimpleNoMatch")) return;

	string expected = "";
	compareResult(expected, str->formatChoice(3.0, map<string, string>()), "testStringFormatChoiceSimpleNoMatch");
	delete str;
}

void testStringFormatChoiceSimpleDefault() {
	IString* str = new IString("1#first string|2#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceSimpleDefault")) return;

	string expected = "other string";
	compareResult(expected, str->formatChoice(3.0, map<string, string>()), "testStringFormatChoiceSimpleDefault");
	delete str;
}

void testStringFormatChoiceLessThanOrEqualPositive() {
	IString* str = new IString("<=2#first string|3#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceLessThanOrEqualPositive")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(1.0, map<string, string>()), "testStringFormatChoiceLessThanOrEqualPositive");
	delete str;
}

void testStringFormatChoiceLessThanOrEqualEqual() {
	IString* str = new IString("<=2#first string|3#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceLessThanOrEqualEqual")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(2.0, map<string, string>()), "testStringFormatChoiceLessThanOrEqualEqual");
	delete str;
}

 void testStringFormatChoiceLessThanOrEqualNotLessThan() {
	IString* str = new IString("<=2#first string|3#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceLessThanOrEqualNotLessThan")) return;

	string expected = "second string";
	compareResult(expected, str->formatChoice(3.0, map<string, string>()), "testStringFormatChoiceLessThanOrEqualNotLessThan");
	delete str;
}

void testStringFormatChoiceGreaterThanOrEqualPositive() {
	IString* str = new IString(">=2#first string|1#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceGreaterThanOrEqualPositive")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(4.0, map<string, string>()), "testStringFormatChoiceGreaterThanOrEqualPositive");
	delete str;
}

void testStringFormatChoiceGreaterThanOrEqualEqual() {
	IString* str = new IString(">=2#first string|1#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceGreaterThanOrEqualEqual")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(2.0, map<string, string>()), "testStringFormatChoiceGreaterThanOrEqualEqual");
	delete str;
}

void testStringFormatChoiceGreaterThanOrEqualNotLessThan() {
	IString* str = new IString(">=2#first string|1#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceGreaterThanOrEqualNotLessThan")) return;

	string expected = "second string";
	compareResult(expected, str->formatChoice(1.0, map<string, string>()), "testStringFormatChoiceGreaterThanOrEqualNotLessThan");
	delete str;
}

void testStringFormatChoiceLessThanPositive() {
	IString* str = new IString("<2#first string|3#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceLessThanPositive")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(1.0, map<string, string>()), "testStringFormatChoiceLessThanPositive");
	delete str;
}

void testStringFormatChoiceLessThanEqual() {
	IString* str = new IString("<2#first string|3#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceLessThanEqual")) return;

	string expected = "other string";
	compareResult(expected, str->formatChoice(2.0, map<string, string>()), "testStringFormatChoiceLessThanEqual");
	delete str;
}

void testStringFormatChoiceLessThanNotLessThan() {
	IString* str = new IString("<2#first string|3#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceLessThanNotLessThan")) return;

	string expected = "second string";
	compareResult(expected, str->formatChoice(3.0, map<string, string>()), "testStringFormatChoiceLessThanNotLessThan");
	delete str;
}

void testStringFormatChoiceGreaterThanPositive() {
	IString* str = new IString(">2#first string|1#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceGreaterThanPositive")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(4.0, map<string, string>()), "testStringFormatChoiceGreaterThanPositive");
	delete str;
}

void testStringFormatChoiceGreaterThanEqual() {
	IString* str = new IString(">2#first string|1#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceGreaterThanEqual")) return;

	string expected = "other string";
	compareResult(expected, str->formatChoice(2.0, map<string, string>()), "testStringFormatChoiceGreaterThanEqual");
	delete str;
}

void testStringFormatChoiceGreaterThanNotLessThan() {
	IString* str = new IString(">2#first string|1#second string|#other string");

	if (assertNotNull(str, "testStringFormatChoiceGreaterThanNotLessThan")) return;

	string expected = "second string";
	compareResult(expected, str->formatChoice(1.0, map<string, string>()), "testStringFormatChoiceGreaterThanNotLessThan");
	delete str;
}

void testStringFormatRange1() {
	IString* str = new IString("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNotNull(str, "testStringFormatRange1")) return;

	int num = 1;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("num", intToString(num)));

	string expected = "first string 1";
	compareResult(expected, str->formatChoice((double)num, values), "testStringFormatRange1");
	delete str;
}

void testStringFormatRange4() {
	IString* str = new IString("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNotNull(str, "testStringFormatRange4")) return;

	int num = 4;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("num", intToString(num)));

	string expected = "second string 4";
	compareResult(expected, str->formatChoice((double)num, values), "testStringFormatRange4");
	delete str;
}

void testStringFormatRange7() {
	IString* str = new IString("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNotNull(str, "testStringFormatRange7")) return;

	int num = 7;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("num", intToString(num)));

	string expected = "other string 7";
	compareResult(expected, str->formatChoice((double)num, values), "testStringFormatRange7");
	delete str;
}

void testStringFormatRange1JSON() {
	IString* str = new IString("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNotNull(str, "testStringFormatRange1JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "1");

	string expected = "first string 1";
	compareResult(expected, str->formatChoice(1.0, json), "testStringFormatRange1JSON");
	delete str;
}

void testStringFormatRange4JSON() {
	IString* str = new IString("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNotNull(str, "testStringFormatRange4JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "4");

	string expected = "second string 4";
	compareResult(expected, str->formatChoice(4.0, json), "testStringFormatRange4JSON");
	delete str;
}

void testStringFormatRange7JSON() {
	IString* str = new IString("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNotNull(str, "testStringFormatRange7JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "7");

	string expected = "other string 7";
	compareResult(expected, str->formatChoice(7.0, json), "testStringFormatRange7JSON");
	delete str;
}

void testStringFormatChoiceBooleanTrue() {
	IString* str = new IString("true#first string|false#second string");

	if (assertNotNull(str, "testStringFormatChoiceBooleanTrue")) return;

	bool value = true;
	string expected = "first string";
	compareResult(expected, str->formatChoice(value, map<string, string>()), "testStringFormatChoiceBooleanTrue");
	delete str;
}

void testStringFormatChoiceBooleanFalse() {
	IString* str = new IString("true#first string|false#second string");

	if (assertNotNull(str, "testStringFormatChoiceBooleanFalse")) return;

	bool value = false;
	string expected = "second string";
	compareResult(expected, str->formatChoice(value, map<string, string>()), "testStringFormatChoiceBooleanFalse");
	delete str;
}

void testStringFormatChoiceBooleanTrueAsInteger() {
	IString* str = new IString("true#first string|false#second string");

	if (assertNotNull(str, "testStringFormatChoiceBooleanTrueAsInteger")) return;

	string expected = "first string";
	compareResult(expected, str->formatChoice(1.0, map<string, string>()), "testStringFormatChoiceBooleanTrueAsInteger");
	delete str;
}

void testStringFormatChoiceBooleanFalseAsInteger() {
	IString* str = new IString("true#first string|false#second string");

	if (assertNotNull(str, "testStringFormatChoiceBooleanFalseAsInteger")) return;

	string expected = "second string";
	compareResult(expected, str->formatChoice(0.0, map<string, string>()), "testStringFormatChoiceBooleanFalseAsInteger");
	delete str;
}

void testStringFormatChoiceBooleanMissing() {
	IString* str = new IString("true#first string");

	if (assertNotNull(str, "testStringFormatChoiceBooleanMissing")) return;

	string expected = "";
	bool value = false;
	compareResult(expected, str->formatChoice(value, map<string, string>()), "testStringFormatChoiceBooleanMissing");
	delete str;
}

void testStringFormatChoiceBooleanWithParams() {
	IString* str = new IString("true#first string {name}|false#second string {name}");

	if (assertNotNull(str, "testStringFormatChoiceBooleanWithParams")) return;

	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("name", "joe"));

	string expected = "second string joe";
	compareResult(expected, str->formatChoice(false, values), "testStringFormatChoiceBooleanWithParams");
	delete str;
}

void testStringFormatChoiceBooleanWithParamsJSON() {
	IString* str = new IString("true#first string {name}|false#second string {name}");

	if (assertNotNull(str, "testStringFormatChoiceBooleanWithParamsJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("name", "joe");

	string expected = "second string joe";
	compareResult(expected, str->formatChoice(false, json), "testStringFormatChoiceBooleanWithParamsJSON");
	delete str;
}

void testStringFormatChoiceStringStaticA() {
   IString* str = new IString("a#first string|b#second string|c#third string");

   if (assertNotNull(str, "testStringFormatChoiceStringStaticA")) return;

   string expected = "first string";
   string key = "a";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceStringStaticA");
   delete str;
}

void testStringFormatChoiceStringStaticB() {
   IString* str = new IString("a#first string|b#second string|c#third string");

    if (assertNotNull(str, "testStringFormatChoiceStringStaticB")) return;

	string expected = "second string";
	string key = "b";
	compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceStringStaticB");
	delete str;
}

void testStringFormatChoiceStringStaticC() {
   IString* str = new IString("a#first string|b#second string|c#third string");

   if (assertNotNull(str, "testStringFormatChoiceStringStaticC")) return;

   string expected = "third string";
   string key = "c";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceStringStaticC");
   delete str;
}

void testStringFormatChoiceStringIgnoreCase() {
   IString* str = new IString("a#first string|b#second string|c#third string");

   if (assertNotNull(str, "testStringFormatChoiceStringIgnoreCase")) return;

   string expected = "second string";
   string key = "B";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceStringIgnoreCase");
   delete str;
}

void testStringFormatChoiceRegExpA() {
   IString* str = new IString("a.*b#first string|b.*c#second string|c+d#third string");

   if (assertNotNull(str, "testStringFormatChoiceRegExpA")) return;

   string expected = "first string";
   string key = "acccb";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceRegExpA");
   delete str;
}

void testStringFormatChoiceRegExpB() {
   IString* str = new IString("a.*b#first string|b.*c#second string|c+d#third string");

   if (assertNotNull(str, "testStringFormatChoiceRegExpB")) return;

   string expected = "second string";
   string key = "bbccc";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceRegExpB");
   delete str;
}

void testStringFormatChoiceRegExpC() {
   IString* str = new IString("a.*b#first string|b.*c#second string|c+d#third string");

   if (assertNotNull(str, "testStringFormatChoiceRegExpC")) return;

   string expected = "third string";
   string key = "ccccd";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceRegExpC");
   delete str;
}

void testStringFormatChoiceRegExpDefault() {
   IString* str = new IString("a.*b#first string|b.*c#second string|#third string");

   if (assertNotNull(str, "testStringFormatChoiceRegExpDefault")) return;

   string expected = "third string";
   string key = "ccccd";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceRegExpDefault");
   delete str;
}

void testStringFormatChoiceRegExpMissing() {
   IString* str = new IString("a.*b#first string|b.*c#second string|c+d#third string");

   if (assertNotNull(str, "testStringFormatChoiceRegExpDefault")) return;

   string expected = "";
   string key = "efff";
   compareResult(expected, str->formatChoice(key, map<string, string>()), "testStringFormatChoiceRegExpDefault");
   delete str;
}

void testStringFormatChoiceWithParams() {
   IString* str = new IString("a.*b#first string {name}|b.*c#second string {name}|c+d#third string {name}");

   if (assertNotNull(str, "testStringFormatChoiceWithParams")) return;

   map<string, string> values = map<string, string>();
   values.insert(pair<string, string>("name", "joe"));

   string expected = "second string joe";
   string key = "bbccc";
   compareResult(expected, str->formatChoice(key, values), "testStringFormatChoiceWithParams");
   delete str;
}

void testStringFormatChoiceWithParamsJSON() {
	IString* str = new IString("a.*b#first string {name}|b.*c#second string {name}|c+d#third string {name}");

	if (assertNotNull(str, "testStringFormatChoiceWithParamsJSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("name", "joe");

	string expected = "second string joe";
	string key = "bbccc";
	compareResult(expected, str->formatChoice(key, json), "testStringFormatChoiceWithParamsJSON");
	delete str;
}

void testStringFormatChoiceWithReplacementZero() {
	IString* str = new IString("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNotNull(str, "testStringFormatChoiceWithReplacementZero")) return;

	int num = 0;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("num", intToString(num)));

    string expected = "There are no strings.";
    compareResult(expected, str->formatChoice(0.0, values), "testStringFormatChoiceWithReplacementZero");
    delete str;
}

void testStringFormatChoiceWithReplacement1() {
	IString* str = new IString("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNotNull(str, "testStringFormatChoiceWithReplacement1")) return;

	int num = 1;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("num", intToString(num)));

    string expected = "There is one string.";
    compareResult(expected, str->formatChoice(1.0, values), "testStringFormatChoiceWithReplacement1");
    delete str;
}

void testStringFormatChoiceWithReplacement2() {
	IString* str = new IString("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNotNull(str, "testStringFormatChoiceWithReplacement2")) return;

	int num = 2;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("num", intToString(num)));

    string expected = "There are 2 strings.";
    compareResult(expected, str->formatChoice(2.0, values), "testStringFormatChoiceWithReplacement2");
    delete str;
}

void testStringFormatChoiceWithReplacement0JSON() {
	IString* str = new IString("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNotNull(str, "testStringFormatChoiceWithReplacement0JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "0");

	string expected = "There are no strings.";
	compareResult(expected, str->formatChoice(0.0, json), "testStringFormatChoiceWithReplacement0JSON");
	delete str;
}

void testStringFormatChoiceWithReplacement1JSON() {
	IString* str = new IString("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNotNull(str, "testStringFormatChoiceWithReplacement1JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "1");

	string expected = "There is one string.";
	compareResult(expected, str->formatChoice(1.0, json), "testStringFormatChoiceWithReplacement1JSON");
	delete str;
}

void testStringFormatChoiceWithReplacement2JSON() {
	IString* str = new IString("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNotNull(str, "testStringFormatChoiceWithReplacement2JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "2");

	string expected = "There are 2 strings.";
	compareResult(expected, str->formatChoice(2.0, json), "testStringFormatChoiceWithReplacement2JSON");
	delete str;
}

void testStringFormatChoiceWithMultipleReplacement0JSON() {
	IString* str = new IString("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNotNull(str, "testStringFormatChoiceWithMultipleReplacement0JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "0");
	json.put("name", "johndoe");

	string expected = "User johndoe has no items.";
	compareResult(expected, str->formatChoice(0.0, json), "testStringFormatChoiceWithMultipleReplacement0JSON");
	delete str;
}

void testStringFormatChoiceWithMultipleReplacement1JSON() {
	IString* str = new IString("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNotNull(str, "testStringFormatChoiceWithMultipleReplacement1JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "1");
	json.put("name", "johndoe");

	string expected = "User johndoe has 1 item.";
	compareResult(expected, str->formatChoice(1.0, json), "testStringFormatChoiceWithMultipleReplacement1JSON");
	delete str;
}

void testStringFormatChoiceWithMultipleReplacement2JSON() {
	IString* str = new IString("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNotNull(str, "testStringFormatChoiceWithMultipleReplacement2JSON")) return;

	pbnjson::JValue json = pbnjson::Object();
	json.put("num", "2");
	json.put("name", "johndoe");

	string expected = "User johndoe has 2 items.";
	compareResult(expected, str->formatChoice(2.0, json), "testStringFormatChoiceWithMultipleReplacement2JSON");
	delete str;
}

void testStringFormatChoiceWithMultipleReplacementZero() {
	IString* str = new IString("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNotNull(str, "testStringFormatChoiceWithMultipleReplacementZero")) return;

	int num = 0;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("name", "johndoe"));
	values.insert(pair<string, string>("num", intToString(num)));

    string expected = "User johndoe has no items.";
    compareResult(expected, str->formatChoice(0.0, values), "testStringFormatChoiceWithMultipleReplacementZero");
    delete str;
}

void testStringFormatChoiceWithMultipleReplacement1() {
	IString* str = new IString("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNotNull(str, "testStringFormatChoiceWithMultipleReplacement1")) return;

	int num = 1;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("name", "Alex"));
	values.insert(pair<string, string>("num", intToString(num)));

    string expected = "User Alex has 1 item.";
    compareResult(expected, str->formatChoice(1.0, values), "testStringFormatChoiceWithMultipleReplacement1");
    delete str;
}

void testStringFormatChoiceWithMultipleReplacement2() {
	IString* str = new IString("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNotNull(str, "testStringFormatChoiceWithMultipleReplacement2")) return;

	int num = 2;
	map<string, string> values = map<string, string>();
	values.insert(pair<string, string>("name", "Edwin"));
	values.insert(pair<string, string>("num", intToString(num)));

    string expected = "User Edwin has 2 items.";
    compareResult(expected, str->formatChoice(2.0, values), "testStringFormatChoiceWithMultipleReplacement2");
    delete str;
}

void testStringFormatMultipleReplacements() {
	IString* str = new IString("User {user} has {num} objects in their {container}.");

	if (assertNotNull(str, "testStringFormatMultipleReplacements")) return;

	map<string, string> values;
	values.insert ( pair<string, string> ("user", "edwin") );
	values.insert ( pair<string, string> ("num", "2") );
	values.insert ( pair<string, string> ("container", "locker") );

	string expected = "User edwin has 2 objects in their locker.";
	compareResult(expected, str->format(values), "testStringFormatMultipleReplacements");
	delete str;
}

void runTestIString(int* testsNumber, int* failuresNumber) {
    cout << "\nRunning TestIString file" << endl;
    cout << "-------------------------------------------------------------" << endl;

    clock_t begin, end, tmp;
    double timeElapsed = .0000;
    short tests_count = 0;

    tmp = clock();
    begin = tmp;
    testStringConstructorFull();
    timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
    cout << "Testcase: testStringConstructorFull took " << timeElapsed << " seconds" << endl;
    tests_count++;

    tmp = clock();
    testStringFormatNoArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatNoArgs took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatEmptyWithArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatEmptyWithArgs took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatWithArg();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatWithArg took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatWithMultipleArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatWithMultipleArgs took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatWithMissingArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatWithMissingArgs took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatWithEmptyArg();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatWithEmptyArg took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatHandleNonAsciiParam();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatHandleNonAsciiParam took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatHandleNonAsciiReplacement();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatHandleNonAsciiReplacement took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatWithArgJSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatWithArgJSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatWithMultipleArgsJSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatWithMultipleArgsJSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatWithMissingArgsJSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatWithMissingArgsJSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement0JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement0JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement1JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement1JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement2JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement2JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimple1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceSimple1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimple2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceSimple2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceOnlyOneChoicePositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceOnlyOneChoicePositive took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceOnlyOneChoiceNegative();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceOnlyOneChoiceNegative took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceNoString();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceNoString took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimpleNoMatch();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceSimpleNoMatch took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimpleDefault();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceSimpleDefault took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanOrEqualEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceLessThanOrEqualEqual took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanOrEqualEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceLessThanOrEqualEqual took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanOrEqualNotLessThan();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceLessThanOrEqualNotLessThan took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanOrEqualPositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceGreaterThanOrEqualPositive took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanOrEqualEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceGreaterThanOrEqualEqual took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanOrEqualNotLessThan();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceGreaterThanOrEqualNotLessThan took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanPositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceLessThanPositive took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceLessThanEqual took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanNotLessThan();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceLessThanNotLessThan took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanPositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceGreaterThanPositive took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceGreaterThanEqual took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanNotLessThan();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceGreaterThanNotLessThan took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatRange1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatRange1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatRange4();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatRange4 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatRange7();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatRange7 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatRange1JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatRange1JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatRange4JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatRange4JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatRange7JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatRange7JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanTrue();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceBooleanTrue took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanFalse();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceBooleanFalse took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanTrueAsInteger();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceBooleanTrueAsInteger took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanFalseAsInteger();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceBooleanFalseAsInteger took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceBooleanMissing took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanWithParams();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceBooleanWithParams took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanWithParamsJSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceBooleanWithParamsJSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringStaticA();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceStringStaticA took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringStaticB();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceStringStaticB took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringStaticC();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceStringStaticC took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringIgnoreCase();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceStringIgnoreCase took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacementZero();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithReplacementZero took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacement1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithReplacement1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacement2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithReplacement2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacementZero();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacementZero took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpA();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceRegExpA took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpB();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceRegExpB took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpC();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceRegExpC took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpDefault();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceRegExpDefault took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceRegExpMissing took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithParams();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithParams took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithParamsJSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithParamsJSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacement0JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithReplacement0JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacement1JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithReplacement1JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacement2JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithReplacement2JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement0JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement0JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement1JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement1JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement2JSON();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testStringFormatChoiceWithMultipleReplacement2JSON took " << timeElapsed << " seconds" << endl;
	tests_count++;

    tmp = clock();
    testStringFormatMultipleReplacements();
    end = clock();
    timeElapsed = ((double)(end - tmp))/CLOCKS_PER_SEC;
    cout << "Testcase: testStringFormatMultipleReplacements took " << timeElapsed << " seconds" << endl;
    tests_count++;

    *testsNumber += tests_count;
    *failuresNumber += iStringTestFailures;
    cout << "Tests run: "<< tests_count << " , Failures: " << iStringTestFailures << ", Time elapsed: " << ((double)(end- begin)/CLOCKS_PER_SEC) << " sec" << endl;
    cout << "---------------------- Standard Output ----------------------" << endl;
}
