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

#include "TestResBundle_C.h"
#include "webosi18n/c/ResBundle_C.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

size_t resBundle_CTestFailures = 0;

/*
bool assertNullC(ResBundleC* resBundle, char* method_name) {
	if (!resBundle) {
		printf("\nTEST_FAILED testname = %s TestResBundle_C ResBundleC is NULL\n", method_name);
		resBundle_CTestFailures++;
		return true;
	}
	return false;
}

void getLocaleSimpleCTest(ResBundleC* resBundle, const char* expected, char* method_name) {
	const char* current_locale = resBundle_getLocale(resBundle);
	if (strcmp(current_locale, expected) != 0) {
		printf("\nTEST_FAILED testname = %s TestResBundle message=error\n", method_name);
		printf("	Expected: %s, actual: %s\n", expected, current_locale);
		resBundle_CTestFailures++;
	}
	free( (char*)current_locale );
}

void containsSourseSimpleCTest(ResBundleC* resBundle, const char* source, bool existed, char* method_name) {
	bool result = resBundle_containsSource(resBundle, source);
	if (result != existed) {
		printf("\nTEST_FAILED testname = %s TestResBundle message=error\n", method_name);
		printf("	Source: %s, is not found\n", source);
		resBundle_CTestFailures++;
	}
}

void getLocStringSingleCTest(ResBundleC* resBundle, const char* source, const char* expected, char* method_name) {
	const char* result = resBundle_getLocString(resBundle, source);
	if (strcmp(result, expected) != 0) {
		printf("\nTEST_FAILED testname = %s TestResBundle message=error\n", method_name);
		printf("	Expected: %s, actual: %s\n", expected, result);
		resBundle_CTestFailures++;
	}
	free( (char*)result );
}

/*
void getLocStringWithKeySingleCTest(ResBundleC* resBundle, const char* key, const char* source, const char* expected, char* method_name) {
	const char* result = resBundle_getLocStringWithKey(resBundle, key, source);
	if (strcmp(result, expected) != 0) {
		printf("\nTEST_FAILED testname = %s TestResBundle message=error\n", method_name);
		printf("	Expected: %s, actual: %s\n", expected, result);
		resBundle_CTestFailures++;
	}
	free( (char*)result );
}

void getLocStringSingleBufferCTest(ResBundleC* resBundle, const char* source, const char* expected,
		char* buffer, size_t buffer_size, char* method_name) {
	const char* result = resBundle_getLocStringBuffer(resBundle, source, buffer, buffer_size);
	if (strcmp(result, expected) != 0) {
		printf("\nTEST_FAILED testname = %s TestResBundle message=error\n", method_name);
		printf("	Expected: %s, actual: %s\n", expected, result);
		resBundle_CTestFailures++;
	}
	free( (char*)result );
}

void getLocStringSingleBufferNotEqualsCTest(ResBundleC* resBundle, const char* source, const char* expected,
		char* buffer, size_t buffer_size, char* method_name) {
	const char* result = resBundle_getLocStringBuffer(resBundle, source, buffer, buffer_size);
	if (strcmp(result, expected) == 0) {
		printf("\nTEST_FAILED testname = %s TestResBundle message=error\n", method_name);
		printf("	Expected: %s, actual: %s\n", expected, result);
		resBundle_CTestFailures++;
	}
	free( (char*)result );
}

void testResBundleCFilepathConstructor()
{
	ResBundleC* bundle = resBundle_create("uk-UA", "res/strings.json");

	if (assertNullC(bundle, "testResBundleCFilepathConstructor")) return;

	resBundle_destroy(bundle);
}

void testResBundleCFileAndPathConstructor()
{
	const char* localeUkrainian = "uk-UA";
	const char* file = "strings.json";
	const char* resources_path = "res";
	ResBundleC* bundle = resBundle_createWithRootPath(localeUkrainian, file, resources_path);

	if (assertNullC(bundle, "testResBundleCFileAndPathConstructor")) return;

	resBundle_destroy(bundle);
}

void testResBundleCEmptyLocale()
{
	const char* emptyLocale = "";
	const char* file_path = "res/strings.json";
	ResBundleC* bundle = resBundle_create(emptyLocale, file_path);

	if (assertNullC(bundle, "testNativeEmptyLocale")) return;

	getLocaleSimpleCTest(bundle, "en-US", "testNativeEmptyLocale");
	resBundle_destroy(bundle);
}

void testResBundleCGetLocaleMexican()
{
	const char* testLocale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(testLocale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocaleMexican")) return;

	getLocaleSimpleCTest(resBundle, testLocale, "testResBundleCGetLocaleMexican");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocaleChinese()
{
	const char* testLocale = "zh-Hans-CN";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(testLocale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocaleChinese")) return;

	getLocaleSimpleCTest(resBundle, testLocale, "testResBundleCGetLocaleChinese");
	resBundle_destroy(resBundle);
}

void testResBundleCContainsSource1()
{
	const char* locale = "fr-FR";
	const char* file_path = "res/cppstrings.json";
	const char* source = "Save title";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCContainsSource1")) return;

	containsSourseSimpleCTest(resBundle, source, true, "testResBundleCContainsSource1");
	resBundle_destroy(resBundle);
}

void testResBundleCContainsSource2()
{
	const char* locale = "fr-FR";
	const char* file_path = "res/cppstrings.json";
	const char* source = "Refresh label";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCContainsSource2")) return;

	containsSourseSimpleCTest(resBundle, source, true, "testResBundleCContainsSource2");
	resBundle_destroy(resBundle);
}

void testResBundleCContainsSource3()
{
	const char* locale = "fr-FR";
	const char* file_path = "res/cppstrings.json";
	const char* source = "French Add title";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCContainsSource3")) return;

	containsSourseSimpleCTest(resBundle, source, false, "testResBundleCContainsSource3");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocString1()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocString1")) return;

	getLocStringSingleCTest(resBundle, "Opt out failed. Try later", "Falló la opción de no participar. Intenta más tarde", "testResBundleCGetLocString1");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocString2()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocString2")) return;

	getLocStringSingleCTest(resBundle, "Done", "Listo", "testResBundleCGetLocString2");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocString3()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocString3")) return;

	getLocStringSingleCTest(resBundle, "A verification email was sent to {email}.",
			"Se ha enviado un mensaje de verificación a {email}.", "testResBundleCGetLocString3");
	resBundle_destroy(resBundle);
}

void testGetLocStringResBundleCFileAndPathConstructor() {
    const char* locale = "uk-UA";
	const char* file_name = "strings.json";
	const char* resources_path = "res";
	ResBundleC * resBundle = resBundle_createWithRootPath(locale, file_name, resources_path);

    if (assertNullC(resBundle, "testGetLocStringResBundleCFileAndPathConstructor")) return;

    getLocStringSingleCTest(resBundle, "Error", "Помилка", "testGetLocStringResBundleCFileAndPathConstructor");
    getLocStringSingleCTest(resBundle, "Edit Address", "Редагувати адресу", "testGetLocStringResBundleCFileAndPathConstructor");
    resBundle_destroy(resBundle);
}

void testGetLocStringResBundleCCompletePathConstructor() {
    const char* locale = "uk-UA";
	const char* file_name = "strings.json";
	const char* resources_path = "res";
	ResBundleC * resBundle = resBundle_createWithRootPath(locale, file_name, resources_path);

    if (assertNullC(resBundle, "testGetLocStringResBundleCCompletePathConstructor")) return;

    getLocStringSingleCTest(resBundle, "Backup suspended", "Suspended backup", "testGetLocStringResBundleCCompletePathConstructor");
    getLocStringSingleCTest(resBundle, "enter password...", "Please, enter your password", "testGetLocStringResBundleCCompletePathConstructor");
    getLocStringSingleCTest(resBundle, "Forgot password", "Забули пароль?", "testGetLocStringResBundleCCompletePathConstructor");
    resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringBufferCorrect()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringBufferCorrect")) return;

	const size_t buffer_size = 5;
	char array[buffer_size];
	const char* source = "Done";
	const char* expected = "Listo";

	getLocStringSingleBufferCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferCorrect");
	resBundle_destroy(resBundle);
}

/*
void testResBundleCGetLocStringBufferIncorrectSize()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringBufferIncorrectSize")) return;

	const size_t buffer_size = 4;
	char* array = malloc(sizeof(char) * buffer_size);
	const char* source = "Done";
	const char* expected = "Listo";

	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBuffer");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringBufferZeroSize()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringBufferZeroSize")) return;

	const size_t buffer_size = 36;
	char* array = malloc(sizeof(char) * buffer_size);
	const char* source = "Done";
	const char* expected = "Listo";

	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, array, 0, "testResBundleCGetLocStringBufferZeroSize");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringBufferLongString()
{
	const char* locale = "de-DE";
	const char* file_path = "res/strings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringBufferLongString")) return;

	size_t buffer_size = 60;
	char array[buffer_size];
	const char* source = "If you turn off Backup, your device will no longer back up your data and your current back up will be erased.";
	const char* expected = "Wenn Sie die Sicherung deaktivieren, werden Ihre Daten nicht mehr gesichert; bereits gesicherte Daten werden gelöscht.";
	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferLongString");

	buffer_size = 100;
	char new_array[buffer_size];
	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, new_array, buffer_size, "testResBundleCGetLocStringBufferLongString");

	buffer_size = 120;
	char other_array[buffer_size];
	getLocStringSingleBufferCTest(resBundle, source, expected, other_array, buffer_size, "testResBundleCGetLocStringBufferLongString");

	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringBufferNull()
{
	ResBundleC* resBundle = NULL;
	const char* source = "Done";
	const char* expected = "Listo";
	size_t buffer_size = 12;
	char other_array[buffer_size];
	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, other_array, buffer_size, "testResBundleCGetLocStringBufferNull");
}

void testResBundleCGetLocStringBufferNonEmpty()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringBufferNonEmpty")) return;

	const size_t buffer_size = 60;
	char* array = malloc(sizeof(char) * buffer_size);
	array = "USE THIS STUFF";
	const char* source = "A verification email was sent to {email}.";
	const char* expected = "Se ha enviado un mensaje de verificación a {email}.";

	getLocStringSingleBufferCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferNonEmpty");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringBufferRealloc()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringBufferRealloc")) return;

	size_t buffer_size = 10;
	char* array = malloc(sizeof(char) * buffer_size);
	char* source = "Done";
	char* expected = "Listo";
	getLocStringSingleBufferCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferRealloc");

	buffer_size = 45;
	array = (char*)realloc(array, sizeof(char) * buffer_size);
	source = "Opt out failed. Try later";
	expected = "Falló la opción de no participar. Intenta más tarde";
	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferRealloc");

	buffer_size = 55;
	array = (char*)realloc(array, sizeof(char) * buffer_size);
	getLocStringSingleBufferCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferNonEmpty");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringBufferMultipleCalls()
{
	const char* locale = "fr-FR";
	const char* file_path = "res/cppstrings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringBufferMultipleCalls")) return;

	size_t buffer_size = 15;
	char* array = malloc(sizeof(char) * buffer_size);
	char* source = "Save title";
	char* expected = "French Save title";
	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferMultipleCalls");

	buffer_size = 19;
	array = (char*)realloc(array, sizeof(char) * buffer_size);
	getLocStringSingleBufferCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferMultipleCalls");

	buffer_size = 65;
	array = malloc(sizeof(char) * buffer_size);
	source = "If you have some questions, send an email";
	expected = "French If you have some questions, send an email";
	getLocStringSingleBufferCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferMultipleCalls");

	buffer_size = 24;
	array = malloc(sizeof(char) * buffer_size);
	source = "Switch to mode";
	expected = "French Switch to mode";
	getLocStringSingleBufferCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferMultipleCalls");

	buffer_size = 11;
	array = (char*)realloc(array, sizeof(char) * buffer_size);
	getLocStringSingleBufferNotEqualsCTest(resBundle, source, expected, array, buffer_size, "testResBundleCGetLocStringBufferMultipleCalls");

	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringWithExistedKey1()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringWithExistedKey1")) return;

	getLocStringWithKeySingleCTest(resBundle, "Opt out failed. Try later", "Try later",
			"Falló la opción de no participar. Intenta más tarde", "testResBundleCGetLocStringWithExistedKey1");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringWithExistedKey2()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringWithExistedKey2")) return;

	getLocStringWithKeySingleCTest(resBundle, "Done", "All is done!", "Listo", "testResBundleCGetLocStringWithExistedKey2");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringWithExistedKey3()
{
	const char* locale = "es-MX";
	const char* file_path = "res/stringsMX.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringWithExistedKey3")) return;

	getLocStringWithKeySingleCTest(resBundle, "A verification email was sent to {email}.", "Email verification sent",
			"Se ha enviado un mensaje de verificación a {email}.", "testResBundleCGetLocStringWithExistedKey3");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringWithNonExistedKey1()
{
	const char* locale = "fr-FR";
	const char* file_path = "res/cppstrings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringWithNonExistedKey1")) return;

	getLocStringWithKeySingleCTest(resBundle, "refreshlabel", "Refresh label", "Refresh label", "testResBundleCGetLocStringWithNonExistedKey1");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringWithNonExistedKey2()
{
	const char* locale = "fr-FR";
	const char* file_path = "res/cppstrings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringWithNonExistedKey2")) return;

	getLocStringWithKeySingleCTest(resBundle, "savetitle", "Save title", "Save title", "testResBundleCGetLocStringWithNonExistedKey2");
	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringMultipleTimes()
{
	const char* locale = "de-DE";
	const char* file_path = "res/strings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringMultipleTimes")) return;

	getLocStringSingleCTest(resBundle, "If you continue to have problems, visit palm.com/support.",
			"Falls das Problem weiterhin auftritt, informieren Sie sich bitte unter palm.com/support.", "testResBundleCGetLocStringMultipleTimes");
	getLocStringSingleCTest(resBundle, "Turning Backup off", "Sicherung wird deaktiviert", "testResBundleCGetLocStringMultipleTimes");
	getLocStringSingleCTest(resBundle, "confirm password...", "Kennwort bestätigen…", "testResBundleCGetLocStringMultipleTimes");
	getLocStringSingleCTest(resBundle, "Backup failure", "Sicherung fehlgeschlagen", "testResBundleCGetLocStringMultipleTimes");
	getLocStringSingleCTest(resBundle, "Turn Backup on to start backing up your data automatically.",
				"Aktivieren Sie die Sicherung, damit Ihre Daten automatisch gesichert werden.", "testResBundleCGetLocStringMultipleTimes");
	getLocStringSingleCTest(resBundle, "Turning Backup off", "Sicherung wird deaktiviert", "testResBundleCGetLocStringMultipleTimes");

	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringMultipleTimesCrissCross()
{
	const char* locale = "de-DE";
	const char* file_path = "res/strings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringMultipleTimesCrissCross")) return;

	getLocStringSingleCTest(resBundle, "Settings", "Einstellungen", "testResBundleCGetLocStringMultipleTimesCrissCross");
	getLocStringSingleCTest(resBundle, "Back Up Now", "Jetzt sichern", "testResBundleCGetLocStringMultipleTimes");
	getLocStringSingleCTest(resBundle, "Settings", "Einstellungen", "testResBundleCGetLocStringMultipleTimesCrissCross");
	getLocStringSingleCTest(resBundle, "Back Up Now", "Jetzt sichern", "testResBundleCGetLocStringMultipleTimes");
	getLocStringSingleCTest(resBundle, "Settings", "Einstellungen", "testResBundleCGetLocStringMultipleTimesCrissCross");
	getLocStringSingleCTest(resBundle, "Settings", "Einstellungen", "testResBundleCGetLocStringMultipleTimesCrissCross");
	getLocStringSingleCTest(resBundle, "Back Up Now", "Jetzt sichern", "testResBundleCGetLocStringMultipleSameCallsInTime");

	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringMultipleSameCallsInTime()
{
	const char* locale = "de-DE";
	const char* file_path = "res/strings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringMultipleSameCallsInTime")) return;

	getLocStringSingleCTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Error", "Fehler", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Help", "Hilfe", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Sign in", "Anmelden", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Turn Off and Erase Backup", "Deakt./gesich. Daten löschen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleCTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");

	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringMultipleCrissCrossWithKeys()
{
	const char* locale = "de-DE";
	const char* file_path = "res/strings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringMultipleCrissCrossWithKeys")) return;

	getLocStringWithKeySingleCTest(resBundle, "preparingitem", "Preparing", "Preparing",
			"testResBundleCGetLocStringMultipleCrissCrossWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "HPaccountSaved", "HP webOS Account saved", "HP webOS Account saved",
			"testResBundleCGetLocStringMultipleCrissCrossWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testResBundleCGetLocStringMultipleCrissCrossWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "emailsending", "Sending password reset email", "Sending password reset email",
			"testResBundleCGetLocStringMultipleCrissCrossWithKeys");

	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys()
{
	const char* locale = "de-DE";
	const char* file_path = "res/strings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys")) return;

	getLocStringWithKeySingleCTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
				"testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "error.", "Error", "Error", "testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "Select a question", "question", "Frage auswählen",
			"testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
				"testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "keepbackup", "Keep Backup On", "Keep Backup On",
			"testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "Sign in", "Sign in", "Anmelden",
			"testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "Keep Backup On", "whatever", "Sicherung aktiviert lassen",
			"testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleCTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys");

	resBundle_destroy(resBundle);
}

void testResBundleCGetLocStringMultipleDifferentCalls()
{
	const char* locale = "de-DE";
	const char* file_path = "res/strings.json";
	ResBundleC * resBundle = resBundle_create(locale, file_path);

	if (assertNullC(resBundle, "testResBundleCGetLocStringMultipleDifferentCalls")) return;

	getLocStringSingleCTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleCTest(resBundle, "Enter password", "Enter password", "Enter password",
			"testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleCTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringSingleCTest(resBundle, "enter password...", "Kennwort eingeben…",
			"testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringSingleCTest(resBundle, "Backup server unavailable", "Sicherungsserver nicht verfügbar",
			"testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleCTest(resBundle, "Backup server unavailable", "Help", "Sicherungsserver nicht verfügbar",
			"testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringSingleCTest(resBundle, "Don't Update", "Nicht aktualisieren", "testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleCTest(resBundle, "don't", "Don't Update", "Don't Update", "testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringSingleCTest(resBundle, "enter password...", "Kennwort eingeben…",
				"testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleCTest(resBundle, "We will send your confirmation email as soon as you have an internet connection.",
			"..............", "Sie erhalten eine Bestätigungs-E-Mail, sobald eine Internetverbindung hergestellt ist.",
			"testResBundleCGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleCTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
				"testResBundleCGetLocStringMultipleDifferentCalls");

	resBundle_destroy(resBundle);
}
*/

void runTestResBundle_C(int* testsNumber, int* failuresNumber)
{
	printf("\nRunning TestResBundle_C file\n");

	clock_t begin, end, tmp;
	double timeElapsed = .0000;
	short tests_count = 0;

	/*
	tmp = clock();
	begin = tmp;
	testResBundleCFilepathConstructor();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCFilepathConstructor took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCFileAndPathConstructor();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCFileAndPathConstructor took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCEmptyLocale();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCEmptyLocale took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocaleMexican();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocaleMexican took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocaleChinese();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocaleChinese took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCContainsSource1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCContainsSource1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCContainsSource2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCContainsSource2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCContainsSource3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCContainsSource3 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocString1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocString1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocString2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocString2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocString3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocString3 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testGetLocStringResBundleCFileAndPathConstructor();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testGetLocStringResBundleCFileAndPathConstructor took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testGetLocStringResBundleCCompletePathConstructor();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testGetLocStringResBundleCCompletePathConstructor took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferCorrect();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferCorrect took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferIncorrectSize();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferIncorrectSize took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferZeroSize();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferZeroSize took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferLongString();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferLongString took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferNull();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferNull took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferNonEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferNonEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferRealloc();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferRealloc took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringBufferMultipleCalls();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringBufferMultipleCalls took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringWithExistedKey1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringWithExistedKey1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringWithExistedKey2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringWithExistedKey2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringWithExistedKey3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringWithExistedKey3 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringWithNonExistedKey1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringWithNonExistedKey1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringWithNonExistedKey2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringWithNonExistedKey2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringMultipleTimes();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringMultipleTimes took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringMultipleTimesCrissCross();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringMultipleTimesCrissCross took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringMultipleSameCallsInTime();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringMultipleSameCallsInTime took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringMultipleCrissCrossWithKeys();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringMultipleCrissCrossWithKeys took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringMultipleSameCallsInTimeWithKeys took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testResBundleCGetLocStringMultipleDifferentCalls();
	end = clock();
	timeElapsed = ((double)(end - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testResBundleCGetLocStringMultipleDifferentCalls took %f seconds\n", timeElapsed);
	tests_count++;
	 */

	*testsNumber += tests_count;
	*failuresNumber += resBundle_CTestFailures;
	printf("Tests run: %i , Failures: %i, Time elapsed: %f sec\n", tests_count, resBundle_CTestFailures, ((double)(end- begin)/CLOCKS_PER_SEC));
	printf("---------------------- Standard Output ----------------------\n");
}


