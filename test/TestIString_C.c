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

#include "TestIString_C.h"
#include "webosi18n/c/IString_C.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

size_t failures_count = 0;

bool assertNull(IStringC* iString, const char* message) {
	if (iString == NULL) {
		printf("\nTEST_FAILED testname = %s TestResBundle_C message=error\n", message);
		++failures_count;
		return true;
	}
	return false;
}

void assertStringEquals(const char* current_result, const char* expected, const char* method_name)
{
	if(strcmp(current_result, expected) != 0) {
		printf("\nTEST_FAILED testname = %s TestIString_C message=error\n", method_name);
		printf("\nTEST_FAILED actual %s\n", current_result);
		++failures_count;
	}
	free((char*) current_result);
}

void testStringConstructorFull()
{
	const char* text = "test test test";
	IStringC* iString = IString_create(text);

	if (assertNull(iString, "testStringConstructorFull")) return;

	int expected_length = 14;
	if (expected_length != IString_length(iString)) {
		printf("\nTEST_FAILED testname = testNativeConstructorNotNull TestIString_C message=error\n");
		++failures_count;
	} else {
		const char* expected = "test test test";
		assertStringEquals(IString_toString(iString), expected, "testNativeConstructorNotNull");
	}

	IString_destroy(iString);
	text = NULL;
}

void testStringFormatNoArgs()
{
	const char* source = "Format this string.";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatNoArgs")) return;

	StringMap* mapPointer = stringMap_create();
	const char* current_result = IString_format(iString, mapPointer);
	free(mapPointer);
	assertStringEquals(current_result, source, "testStringFormatNoArgs");
	IString_destroy(iString);
	source = NULL;
}

void testStringFormatEmpty() {
	const char* source = "";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatEmpty")) return;

	assertStringEquals(IString_toString(iString), source, "testStringFormatEmpty");
	IString_destroy(iString);
}

void testStringFormatEmptyWithArgs() {
	const char* source = "";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatEmptyWithArgs")) return;

	PairItem itemTest = {"test", "Foo"};
	StringMap* mapPointer = stringMap_create();
	stringMap_addItem(mapPointer, &itemTest);

	assertStringEquals(IString_format(iString, mapPointer), source, "testStringFormatEmptyWithArgs");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatWithArg() {
	const char* source = "Format {size} string.";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatWithArg")) return;

	StringMap* mapPointer = stringMap_create();
	PairItem itemTest = {"size", "medium"};
	stringMap_addItem(mapPointer, &itemTest);

	assertStringEquals(IString_format(iString, mapPointer), "Format medium string.", "testStringFormatWithArg");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatWithMultipleArgs() {
	const char* source = "Format {size} {object}.";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatWithMultipleArgs")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "size", "medium");
	stringMap_addKeyValue(mapPointer, "object", "string");

	assertStringEquals(IString_format(iString, mapPointer), "Format medium string.", "testStringFormatWithMultipleArgs");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatWithMissingArgs() {
	const char* source = "Format {size} {object}.";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatWithMissingArgs")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "object", "string");
	assertStringEquals(IString_format(iString, mapPointer), "Format {size} string.", "testStringFormatWithMissingArgs");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatWithEmptyArg() {
	const char* source = "Format {size} string.";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatWithEmptyArg")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "size", "");

	assertStringEquals(IString_format(iString, mapPointer), "Format  string.", "testStringFormatWithEmptyArg");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatHandleNonAsciiParam() {
	const char* source = "Format {size} string.";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatHandleNonAsciiParam")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "size", "médïûm");

	assertStringEquals(IString_format(iString, mapPointer), "Format médïûm string.", "testStringFormatHandleNonAsciiParam");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatHandleNonAsciiReplacement() {
	const char* source = "Format {sïzé} string.";
	IStringC* iString = IString_create(source);

	if (assertNull(iString, "testStringFormatHandleNonAsciiReplacement")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "sïzé", "medium");

	assertStringEquals(IString_format(iString, mapPointer), "Format medium string.", "testStringFormatHandleNonAsciiReplacement");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceSimple1() {
	IStringC* iString = IString_create("1#first string|2#second string");

	if (assertNull(iString, "testStringFormatChoiceSimple1")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 1.0, mapPointer), "first string", "testStringFormatChoiceSimple1");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceSimple2() {
	IStringC* iString = IString_create("1#first string|2#second string");

	if (assertNull(iString, "testStringFormatChoiceSimple2")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 2.0, mapPointer), "second string", "testStringFormatChoiceSimple2");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceOnlyOneChoicePositive() {
	IStringC* iString = IString_create("1#first string");

	if (assertNull(iString, "testStringFormatChoiceOnlyOneChoicePositive")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 1.0, mapPointer), "first string", "testStringFormatChoiceOnlyOneChoicePositive");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceOnlyOneChoiceNegative() {
	IStringC* iString = IString_create("1#first string");

	if (assertNull(iString, "testStringFormatChoiceOnlyOneChoiceNegative")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 2.0, mapPointer), "", "testStringFormatChoiceOnlyOneChoiceNegative");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceNoString() {
	IStringC* iString = IString_create("");

	if (assertNull(iString, "testStringFormatChoiceNoString")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 2.0, mapPointer), "", "testStringFormatChoiceNoString");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceSimpleNoMatch() {
	IStringC* iString = IString_create("1#first string|2#second string");

	if (assertNull(iString, "testStringFormatChoiceSimpleNoMatch")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 3.0, mapPointer), "", "testStringFormatChoiceSimpleNoMatch");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceSimpleDefault() {
	IStringC* iString = IString_create("1#first string|2#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceSimpleDefault")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 3.0, mapPointer), "other string", "testStringFormatChoiceSimpleDefault");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceLessThanOrEqualPositive() {
	IStringC* iString = IString_create("<=2#first string|3#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceLessThanOrEqualPositive")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 1.0, mapPointer), "first string", "testStringFormatChoiceLessThanOrEqualPositive");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceLessThanOrEqualEqual() {
	IStringC* iString = IString_create("<=2#first string|3#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceLessThanOrEqualEqual")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 2.0, mapPointer), "first string", "testStringFormatChoiceLessThanOrEqualEqual");
	free(mapPointer);
	IString_destroy(iString);
}

 void testStringFormatChoiceLessThanOrEqualNotLessThan() {
	 IStringC* iString = IString_create("<=2#first string|3#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceLessThanOrEqualNotLessThan")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 3.0, mapPointer), "second string", "testStringFormatChoiceLessThanOrEqualNotLessThan");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceGreaterThanOrEqualPositive() {
	IStringC* iString = IString_create(">=2#first string|1#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceGreaterThanOrEqualPositive")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 4.0, mapPointer), "first string", "testStringFormatChoiceGreaterThanOrEqualPositive");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceGreaterThanOrEqualEqual() {
	IStringC* iString = IString_create(">=2#first string|1#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceGreaterThanOrEqualEqual")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 2.0, mapPointer), "first string", "testStringFormatChoiceGreaterThanOrEqualEqual");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceGreaterThanOrEqualNotLessThan() {
	IStringC* iString = IString_create(">=2#first string|1#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceGreaterThanOrEqualNotLessThan")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 1.0, mapPointer), "second string", "testStringFormatChoiceGreaterThanOrEqualNotLessThan");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceLessThanPositive() {
	IStringC* iString = IString_create("<2#first string|3#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceLessThanPositive")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 1.0, mapPointer), "first string", "testStringFormatChoiceLessThanPositive");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceLessThanEqual() {
	IStringC* iString = IString_create("<2#first string|3#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceLessThanEqual")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 2.0, mapPointer), "other string", "testStringFormatChoiceLessThanEqual");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceLessThanNotLessThan() {
	IStringC* iString = IString_create("<2#first string|3#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceLessThanNotLessThan")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 3.0, mapPointer), "second string", "testStringFormatChoiceLessThanNotLessThan");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceGreaterThanPositive() {
	IStringC* iString = IString_create(">2#first string|1#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceGreaterThanPositive")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 4.0, mapPointer), "first string", "testStringFormatChoiceGreaterThanPositive");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceGreaterThanEqual() {
	IStringC* iString = IString_create(">2#first string|1#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceGreaterThanEqual")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 2.0, mapPointer), "other string", "testStringFormatChoiceGreaterThanEqual");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceGreaterThanNotLessThan() {
	IStringC* iString = IString_create(">2#first string|1#second string|#other string");

	if (assertNull(iString, "testStringFormatChoiceGreaterThanNotLessThan")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 1.0, mapPointer), "second string", "testStringFormatChoiceGreaterThanNotLessThan");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatRange1() {
	IStringC* iString = IString_create("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNull(iString, "testStringFormatRange1")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "1");
	int num = 1;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "first string 1", "testStringFormatRange1");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatRange4() {
	IStringC* iString = IString_create("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNull(iString, "testStringFormatRange4")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "4");
	int num = 4;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "second string 4", "testStringFormatRange4");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatRange7() {
	IStringC* iString = IString_create("0-2#first string {num}|3-5#second string {num}|#other string {num}");

	if (assertNull(iString, "testStringFormatRange7")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "7");
	int num = 7;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "other string 7", "testStringFormatRange7");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceBooleanTrue() {
	IStringC* iString = IString_create("true#first string|false#second string");

	if (assertNull(iString, "testStringFormatChoiceBooleanTrue")) return;

	bool value = true;
	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceBoolRef(iString, value, mapPointer), "first string", "testStringFormatChoiceBooleanTrue");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceBooleanFalse() {
	IStringC* iString = IString_create("true#first string|false#second string");

	if (assertNull(iString, "testStringFormatChoiceBooleanFalse")) return;

	bool value = false;
	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceBoolRef(iString, value, mapPointer), "second string", "testStringFormatChoiceBooleanFalse");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceBooleanTrueAsInteger() {
	IStringC* iString = IString_create("true#first string|false#second string");

	if (assertNull(iString, "testStringFormatChoiceBooleanTrueAsInteger")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 1.0, mapPointer), "first string", "testStringFormatChoiceBooleanTrueAsInteger");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceBooleanFalseAsInteger() {
	IStringC* iString = IString_create("true#first string|false#second string");

	if (assertNull(iString, "testStringFormatChoiceBooleanFalseAsInteger")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceDoubleRef(iString, 0.0, mapPointer), "second string", "testStringFormatChoiceBooleanFalseAsInteger");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceBooleanMissing() {
	IStringC* iString = IString_create("true#first string");

	if (assertNull(iString, "testStringFormatChoiceBooleanMissing")) return;

	bool value = false;
	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceBoolRef(iString, value, mapPointer), "", "testStringFormatChoiceBooleanMissing");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceBooleanWithParams() {
	IStringC* iString = IString_create("true#first string {name}|false#second string {name}");

	if (assertNull(iString, "testStringFormatChoiceBooleanWithParams")) return;

	bool value = false;
	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "name", "joe");
	assertStringEquals(IString_formatChoiceBoolRef(iString, value, mapPointer), "second string joe", "testStringFormatChoiceBooleanWithParams");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceStringStaticA() {
	IStringC* iString = IString_create("a#first string|b#second string|c#third string");

	if (assertNull(iString, "testStringFormatChoiceStringStaticA")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "a", mapPointer), "first string", "testStringFormatChoiceStringStaticA");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceStringStaticB() {
	IStringC* iString = IString_create("a#first string|b#second string|c#third string");

	if (assertNull(iString, "testStringFormatChoiceStringStaticB")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "b", mapPointer), "second string", "testStringFormatChoiceStringStaticB");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceStringStaticC() {
	IStringC* iString = IString_create("a#first string|b#second string|c#third string");

	if (assertNull(iString, "testStringFormatChoiceStringStaticC")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "c", mapPointer), "third string", "testStringFormatChoiceStringStaticC");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceStringIgnoreCase() {
	IStringC* iString = IString_create("a#first string|b#second string|c#third string");

	if (assertNull(iString, "testStringFormatChoiceStringIgnoreCase")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "B", mapPointer), "second string", "testStringFormatChoiceStringIgnoreCase");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceRegExpA() {
	IStringC* iString = IString_create("a.*b#first string|b.*c#second string|c+d#third string");

	if (assertNull(iString, "testStringFormatChoiceRegExpA")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "acccb", mapPointer), "first string", "testStringFormatChoiceRegExpA");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceRegExpB() {
	IStringC* iString = IString_create("a.*b#first string|b.*c#second string|c+d#third string");

	if (assertNull(iString, "testStringFormatChoiceRegExpB")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "bbccc", mapPointer), "second string", "testStringFormatChoiceRegExpB");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceRegExpC() {
	IStringC* iString = IString_create("a.*b#first string|b.*c#second string|c+d#third string");

	if (assertNull(iString, "testStringFormatChoiceRegExpC")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "ccccd", mapPointer), "third string", "testStringFormatChoiceRegExpC");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceRegExpDefault() {
	IStringC* iString = IString_create("a.*b#first string|b.*c#second string|#third string");

	if (assertNull(iString, "testStringFormatChoiceRegExpDefault")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "ccccd", mapPointer), "third string", "testStringFormatChoiceRegExpDefault");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceRegExpMissing() {
	IStringC* iString = IString_create("a.*b#first string|b.*c#second string|c+d#third string");

	if (assertNull(iString, "testStringFormatChoiceRegExpMissing")) return;

	StringMap* mapPointer = stringMap_create();
	assertStringEquals(IString_formatChoiceStringRef(iString, "efff3N", mapPointer), "", "testStringFormatChoiceRegExpMissing");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceWithParams() {
	IStringC* iString = IString_create("a.*b#first string {name}|b.*c#second string {name}|c+d#third string {name}");

	if (assertNull(iString, "testStringFormatChoiceWithParams")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "name", "joe");
	assertStringEquals(IString_formatChoiceStringRef(iString, "bbccc", mapPointer), "second string joe", "testStringFormatChoiceWithParams");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceWithReplacementZero() {
	IStringC* iString = IString_create("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNull(iString, "testStringFormatChoiceWithReplacementZero")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "0");
	int num = 0;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "There are no strings.", "testStringFormatChoiceWithReplacementZero");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceWithReplacement1() {
	IStringC* iString = IString_create("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNull(iString, "testStringFormatChoiceWithReplacement1")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "1");
	int num = 1;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "There is one string.", "testStringFormatChoiceWithReplacement1");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceWithReplacement2() {
	IStringC* iString = IString_create("0#There are no strings.|1#There is one string.|#There are {num} strings.");

	if (assertNull(iString, "testStringFormatChoiceWithReplacement2")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "2");
	int num = 2;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "There are 2 strings.", "testStringFormatChoiceWithReplacement2");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceWithMultipleReplacementZero() {
	IStringC* iString = IString_create("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNull(iString, "testStringFormatChoiceWithMultipleReplacementZero")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "0");
	stringMap_addKeyValue(mapPointer, "name", "johndoe");
	int num = 0;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "User johndoe has no items.",
			"testStringFormatChoiceWithMultipleReplacementZero");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceWithMultipleReplacement1() {
	IStringC* iString = IString_create("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNull(iString, "testStringFormatChoiceWithMultipleReplacement1")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "1");
	stringMap_addKeyValue(mapPointer, "name", "Alex");
	int num = 1;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "User Alex has 1 item.", "testStringFormatChoiceWithMultipleReplacement1");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatChoiceWithMultipleReplacement2() {
	IStringC* iString = IString_create("0#User {name} has no items.|1#User {name} has {num} item.|#User {name} has {num} items.");

	if (assertNull(iString, "testStringFormatChoiceWithMultipleReplacement2")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "2");
	stringMap_addKeyValue(mapPointer, "name", "Edwin");
	int num = 2;
	assertStringEquals(IString_formatChoiceDoubleRef(iString, (double)num, mapPointer), "User Edwin has 2 items.",
			"testStringFormatChoiceWithMultipleReplacement2");
	free(mapPointer);
	IString_destroy(iString);
}

void testStringFormatMultipleReplacements() {
	IStringC* iString = IString_create("User {user} has {num} objects in their {container}.");

	if (assertNull(iString, "testStringFormatMultipleReplacements")) return;

	StringMap* mapPointer = stringMap_create();
	stringMap_addKeyValue(mapPointer, "num", "2");
	stringMap_addKeyValue(mapPointer, "user", "Edwin");
	stringMap_addKeyValue(mapPointer, "container", "locker");
	assertStringEquals(IString_format(iString, mapPointer), "User Edwin has 2 objects in their locker.", "testStringFormatMultipleReplacements");
	free(mapPointer);
	IString_destroy(iString);
}

void runTestIString_C(int* testsNumber, int* failuresNumber) {
	printf("\nRunning TestIString_C file\n");

	clock_t begin, end, tmp;
	double timeElapsed = .0000;
	short tests_count = 0;

	tmp = clock();
	begin = tmp;
	testStringConstructorFull();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testNativeConstructorNotNull took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatNoArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatNoArgs took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatEmptyWithArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatEmptyWithArgs took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatWithArg();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatWithArg took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatWithMultipleArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatWithMultipleArgs took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatWithMissingArgs();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatWithMissingArgs took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatWithEmptyArg();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatWithEmptyArg took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatHandleNonAsciiParam();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatHandleNonAsciiParam took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatHandleNonAsciiReplacement();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatHandleNonAsciiReplacement took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimple1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceSimple1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimple2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceSimple2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceOnlyOneChoicePositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceOnlyOneChoicePositive took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceOnlyOneChoiceNegative();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceOnlyOneChoiceNegative took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceNoString();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceNoString took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimpleNoMatch();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceSimpleNoMatch took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceSimpleDefault();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceSimpleDefault took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanOrEqualPositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceLessThanOrEqualPositive took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanOrEqualEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceLessThanOrEqualEqual took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanOrEqualNotLessThan();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceLessThanOrEqualNotLessThan took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanOrEqualPositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceGreaterThanOrEqualPositive took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanOrEqualEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceGreaterThanOrEqualEqual took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanOrEqualNotLessThan();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceGreaterThanOrEqualNotLessThan took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanPositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceLessThanPositive took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceLessThanEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceLessThanEqual took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanPositive();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceGreaterThanPositive took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceGreaterThanEqual took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceGreaterThanNotLessThan();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceGreaterThanNotLessThan took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatRange1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatRange1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatRange4();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatRange4 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatRange7();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatRange7 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanTrue();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceBooleanTrue took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanFalse();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceBooleanFalse took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanTrueAsInteger();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceBooleanTrueAsInteger took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanFalseAsInteger();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceBooleanFalseAsInteger took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceBooleanMissing took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceBooleanWithParams();
	end = clock();
	timeElapsed = ((double)(end - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceBooleanWithParams took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringStaticA();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceStringStaticA took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringStaticB();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceStringStaticB took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringStaticC();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceStringStaticC took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceStringIgnoreCase();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceStringIgnoreCase took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpA();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceRegExpA took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpB();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceRegExpB took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpC();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceRegExpC took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpDefault();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceRegExpDefault took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceRegExpMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceRegExpMissing took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithParams();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceWithParams took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacementZero();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceWithReplacementZero took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacement1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceWithReplacement1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithReplacement2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceWithReplacement2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacementZero();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceWithMultipleReplacementZero took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceWithMultipleReplacement1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatChoiceWithMultipleReplacement2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatChoiceWithMultipleReplacement2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testStringFormatMultipleReplacements();
	end = clock();
	timeElapsed = ((double)(end - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testStringFormatMultipleReplacements took %f seconds\n", timeElapsed);
	tests_count++;

	*testsNumber += tests_count;
	*failuresNumber += failures_count;
	printf("Tests run: %i , Failures: %i, Time elapsed: %f sec\n", tests_count, failures_count, ((double)(end- begin)/CLOCKS_PER_SEC));
	printf("---------------------- Standard Output ----------------------\n");
}
