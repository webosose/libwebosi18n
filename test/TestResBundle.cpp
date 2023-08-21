// Copyright (c) 2013-2023 LG Electronics, Inc.
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
 * TestResBundle.cpp
 *
 * @author Oleksandr Gorbunov
 */

#include "webosi18n/cxx/ResBundle.h"
#include "TestResBundle.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/*
 * Simple C++ Test Suite for ResBundle
 */
size_t resBundleTestFailures = 0;

bool assertNull(ResBundle* resBundle, string methodName) {
	if (!resBundle) {
		cout << "\n%TEST_FAILED% testname = " << methodName << " TestResBundle ResBundle is NULL" << endl;
		resBundleTestFailures++;
		return true;
	}
	return false;
}

void getLocaleSimpleTest(ResBundle* resBundle, string currentLocale, string method_name) {
	if (currentLocale.compare(resBundle->getLocale()) != 0) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestResBundle message=error" << endl;
		cout << "		Expetcted: " << currentLocale << ", actual: " << resBundle->getLocale() << endl;
		resBundleTestFailures++;
	}
}

void containsSourseSimpleTest(ResBundle* resBundle, string source, bool existed, string method_name) {
	bool result = resBundle->containsSource(source);
	if (result != existed) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestResBundle message=error" << endl;
		cout << "		Source \"" << source << "\" is not found"<< endl;
		resBundleTestFailures++;
	}
}

void getLocStringSingleTest(ResBundle* resBundle, string source, string expected, string method_name) {
	string result = resBundle->getLocString(source);
	if (result.compare(expected) != 0) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestResBundle message=error" << endl;
		cout << "		Expetcted: \"" << expected << "\"; actual: \"" << result << "\"" << endl;
		resBundleTestFailures++;
	}
}

void getLocStringWithKeySingleTest(ResBundle* resBundle, string key, string source, string expected, string method_name) {
	string result = resBundle->getLocString(key, source);
	if (result.compare(expected) != 0) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestResBundle message=error" << endl;
		cout << "		Expetcted: " << expected << "; actual: " << result << endl;
		resBundleTestFailures++;
	}
}

void testResBundleFilePathConstructor() {
	std::string locale = "uk-UA";
	const std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testResBundleFilePathConstructor")) return;
	delete resBundle;
}

void testResBundleFileAndPathConstructor() {
	std::string locale = "uk-UA";
	const std::string file = "strings.json";
	const std::string resources_path = "res";
	ResBundle* resBundle = new ResBundle(locale, file, resources_path);

	if (assertNull(resBundle, "testResBundleFileAndPathConstructor")) return;
	delete resBundle;
}

void testEmptyLocale() {
	std::string locale("");
	const std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testEmptyLocale")) return;

	getLocaleSimpleTest(resBundle, "en-US", "testEmptyLocale");
	delete resBundle;
}

void testContainsSourceTrue() {
	std::string locale = "fr-FR";
	std::string file_path = "res/cppstrings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testContainsSourceTrue")) return;

	containsSourseSimpleTest(resBundle, "Refresh label", true, "testContainsSourceTrue");
	delete resBundle;
}

void testContainsSourceFalse() {
	std::string locale = "fr-FR";
	std::string file_path = "res/cppstrings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testContainsSourceFalse")) return;

	containsSourseSimpleTest(resBundle, "French Add title", false, "testContainsSourceFalse");
	delete resBundle;
}

void testGetLocString1() {
	std::string locale = "es-MX";
	const std::string file_path = "res/stringsMX.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocString1")) return;

	getLocStringSingleTest(resBundle, "Opt out failed. Try later",
			"Falló la opción de no participar. Intenta más tarde", "testGetLocString1");
	delete resBundle;
}

void testGetPseudoString1()
{
	std::string locale = "zxx-XX";
	ResBundle* resBundle = new ResBundle(locale, "");
	if (assertNull(resBundle, "testGetPseudoString1")) return;

	getLocStringSingleTest(resBundle, "HID device is connected.", "[ĦÏÐ ðëvíçë íš çõññëçţëð.76543210]",
			"testGetPseudoString1");

	delete resBundle;
}

void testGetPseudoString2()
{
	std::string locale = "zxx-Cyrl-XX";
	ResBundle* resBundle = new ResBundle(locale, "", "");
	if (assertNull(resBundle, "testGetPseudoString2")) return;

	getLocStringSingleTest(resBundle, "HID device is connected.", "[ХИД дэвичэ ис чоннэчтэд.76543210]",
			"testGetPseudoString2");

	delete resBundle;
}

void testGetPseudoString3()
{
	std::string locale = "zxx-Hebr-XX";
	ResBundle* resBundle = new ResBundle(locale, "", "");
	if (assertNull(resBundle, "testGetPseudoString3")) return;

	getLocStringSingleTest(resBundle, "HID device is connected.", "[הִדּ דֶבִקֶ ִס קֹננֶקטֶד.76543210]",
			"testGetPseudoString3");

	delete resBundle;
}

void testGetPseudoString4()
{
	std::string locale = "zxx-Hans-XX";
	ResBundle* resBundle = new ResBundle(locale, "", "");
	if (assertNull(resBundle, "testGetPseudoString4")) return;

	getLocStringSingleTest(resBundle, "HID device is connected.", "[ĦИדּ ðэב意çэ 意š ק夥ñнֶ可ţэד.76543210]",
			"testGetPseudoString4");

	delete resBundle;
}

void testGetLocString2() {
	std::string locale = "es-MX";
	const std::string file_path = "res/stringsMX.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocString2")) return;

	getLocStringSingleTest(resBundle, "Done", "Listo", "testGetLocString2");
	delete resBundle;
}

void testGetLocString3() {
	std::string locale = "es-MX";
	const std::string file_path = "res/stringsMX.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocString3")) return;

	getLocStringSingleTest(resBundle, "A verification email was sent to {email}.",
				"Se ha enviado un mensaje de verificación a {email}.", "testGetLocString3");
	delete resBundle;
}

void testGetLocStringResBundleFileAndPathConstructor() {
	std::string locale = "uk-UA";
	const std::string file = "strings.json";
	const std::string resources_path = "res";
	ResBundle* resBundle = new ResBundle(locale, file, resources_path);

	if (assertNull(resBundle, "testGetLocStringResBundleFileAndPathConstructor")) return;

	getLocStringSingleTest(resBundle, "Error", "Помилка", "testGetLocStringResBundleFileAndPathConstructor");
	getLocStringSingleTest(resBundle, "enter password...", "Please, enter your password", "testGetLocStringResBundleFileAndPathConstructor");
	getLocStringSingleTest(resBundle, "Edit Address", "Редагувати адресу", "testGetLocStringResBundleFileAndPathConstructor");
	delete resBundle;
}

void testGetLocStringWithExistedKey1() {
	std::string locale = "es-MX";
	const std::string file_path = "res/stringsMX.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringWithExistedKey1")) return;

	getLocStringWithKeySingleTest(resBundle, "Opt out failed. Try later", "Try later",
			"Falló la opción de no participar. Intenta más tarde", "testGetLocStringWithExistedKey1");
	delete resBundle;
}

void testGetLocStringWithExistedKey2() {
	std::string locale = "es-MX";
	const std::string file_path = "res/stringsMX.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringWithExistedKey2")) return;

	getLocStringWithKeySingleTest(resBundle, "Done", "Task is done!", "Listo", "testGetLocStringWithExistedKey2");
	delete resBundle;
}

void testGetLocStringWithNonExistedKey1() {
	std::string locale = "fr-FR";
	const std::string file_path = "res/cppstrings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringWithNonExistedKey1")) return;

	getLocStringWithKeySingleTest(resBundle, "addtitle", "Add title", "Add title", "testGetLocStringWithNonExistedKey1");
	delete resBundle;
}

void testGetLocStringWithNonExistedKey2() {
	std::string locale = "fr-FR";
	const std::string file_path = "res/cppstrings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringWithNonExistedKey2")) return;

	getLocStringWithKeySingleTest(resBundle, "switchtomode", "Switch to mode", "Switch to mode", "testGetLocStringWithNonExistedKey2");
	delete resBundle;
}

void testGetLocaleWithResourcesGerman() {
	std::string locale = "de-DE";
	std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocaleWithResourcesGerman")) return;

	getLocaleSimpleTest(resBundle, locale, "testGetLocaleWithResourcesGerman");
	delete resBundle;
}

void testGetLocaleWithResourcesMongolian() {
	std::string locale = "mn-Cyrl-MN";
	std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocaleWithResourcesGerman")) return;

	getLocaleSimpleTest(resBundle, locale, "testGetLocaleWithResourcesGerman");
	delete resBundle;
}

void testGetLocStringMultipleTimes() {
	std::string locale = "fr-FR";
	const std::string file_path = "res/cppstrings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringMultipleTimes")) return;

	getLocStringSingleTest(resBundle, "Switch to mode", "French Switch to mode", "testGetLocStringMultipleTimes");
	getLocStringSingleTest(resBundle, "Save title", "French Save title", "testGetLocStringMultipleTimes");
	getLocStringSingleTest(resBundle, "Refresh label", "French Refresh label", "testGetLocStringMultipleTimes");
	getLocStringSingleTest(resBundle, "Refresh label item", "Refresh label item", "testGetLocStringMultipleTimes");
	getLocStringSingleTest(resBundle, "Add title", "French Add title", "testGetLocStringMultipleTimes");

	delete resBundle;
}

void testGetLocStringMultipleTimesCrissCross() {
	std::string locale = "de-DE";
	std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringMultipleTimesCrissCross")) return;

	getLocaleSimpleTest(resBundle, locale, "testGetLocStringMultipleTimesCrissCross");
	getLocStringSingleTest(resBundle, "Settings", "Einstellungen", "testGetLocStringMultipleTimesCrissCross");
	getLocStringSingleTest(resBundle, "Back Up Now", "Jetzt sichern", "testGetLocStringMultipleTimesCrissCross");
	getLocStringSingleTest(resBundle, "Settings", "Einstellungen", "testGetLocStringMultipleTimesCrissCross");
	getLocStringSingleTest(resBundle, "Back Up Now", "Jetzt sichern", "testGetLocStringMultipleTimesCrissCross");
	getLocStringSingleTest(resBundle, "Settings", "Einstellungen", "testGetLocStringMultipleTimesCrissCross");
	getLocStringSingleTest(resBundle, "Settings", "Einstellungen", "testGetLocStringMultipleTimesCrissCross");
	getLocStringSingleTest(resBundle, "Back Up Now", "Jetzt sichern", "testGetLocStringMultipleTimesCrissCross");
	delete resBundle;
}

void testGetLocStringMultipleSameCallsInTime() {
	std::string locale = "de-DE";
	std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringMultipleSameCallsInTime")) return;

	getLocStringSingleTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Error", "Fehler", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Help", "Hilfe", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Sign in", "Anmelden", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Turn Off and Erase Backup", "Deakt./gesich. Daten löschen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	getLocStringSingleTest(resBundle, "Select a question", "Frage auswählen", "testResBundleCGetLocStringMultipleSameCallsInTime");
	delete resBundle;
}

void testGetLocStringMultipleCrissCrossWithKeys()
{
	std::string locale = "de-DE";
	std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringMultipleCrissCrossWithKeys")) return;

	getLocStringWithKeySingleTest(resBundle, "preparingitem", "Preparing", "Preparing",
			"testGetLocStringMultipleCrissCrossWithKeys");
	getLocStringWithKeySingleTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testGetLocStringMultipleCrissCrossWithKeys");
	getLocStringWithKeySingleTest(resBundle, "HPaccountSaved", "HP webOS Account saved", "HP webOS Account saved",
			"testGetLocStringMultipleCrissCrossWithKeys");
	getLocStringWithKeySingleTest(resBundle, "confirm password...", "confirm password", "Kennwort bestätigen…",
			"testGetLocStringMultipleCrissCrossWithKeys");
	getLocStringWithKeySingleTest(resBundle, "emailsending", "Sending password reset email", "Sending password reset email",
			"testGetLocStringMultipleCrissCrossWithKeys");

	delete resBundle;
}

void testGetLocStringMultipleSameCallsInTimeWithKeys()
{
	std::string locale = "de-DE";
	std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringMultipleCrissCrossWithKeys")) return;

	getLocStringWithKeySingleTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleTest(resBundle, "error.", "Error", "Error", "testGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleTest(resBundle, "Select a question", "question", "Frage auswählen",
			"testGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleTest(resBundle, "keepbackup", "Keep Backup On", "Keep Backup On",
			"testGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleTest(resBundle, "Sign in", "Sign in", "Anmelden",
			"testGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleTest(resBundle, "Keep Backup On", "whatever", "Sicherung aktiviert lassen",
			"testGetLocStringMultipleSameCallsInTimeWithKeys");
	getLocStringWithKeySingleTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testGetLocStringMultipleSameCallsInTimeWithKeys");

	delete resBundle;
}

void testGetMultipleResourceBundles()
{
	std::string englishLocale = "en-CN";
	std::string chineseLocale = "zh-Hans-CN";
	const std::string file = "strings.json";
	const std::string resources_path = "res/";
	ResBundle* resBundleEnglish = new ResBundle(englishLocale, file, resources_path);
	ResBundle* resBundleChinese = new ResBundle(chineseLocale, file, resources_path);

	if (assertNull(resBundleEnglish, "testGetMultipleResourceBundles")) return;
	if (assertNull(resBundleChinese, "testGetMultipleResourceBundles")) return;

	getLocStringSingleTest(resBundleEnglish, "Don't Update", "Do not update", "testGetMultipleResourceBundles");
	getLocStringSingleTest(resBundleEnglish, "Change Password", "Password must be changed",
			"testGetMultipleResourceBundles");

	getLocStringSingleTest(resBundleChinese, "Done", "Chinese Done.", "testGetMultipleResourceBundles");
	getLocStringSingleTest(resBundleChinese, "Change Password", "Chinese changing password",
			"testGetMultipleResourceBundles");

	delete resBundleEnglish;

	resBundleEnglish = resBundleChinese;

	getLocStringSingleTest(resBundleEnglish, "Don't Update", "Chinese Do not update", "testGetMultipleResourceBundles");
	getLocStringSingleTest(resBundleEnglish, "Change Password", "Chinese changing password",
			"testGetMultipleResourceBundles");

	delete resBundleChinese;
}

void testGetLocStringMultipleDifferentCalls()
{
	std::string locale = "de-DE";
	std::string file_path = "res/strings.json";
	ResBundle* resBundle = new ResBundle(locale, file_path);

	if (assertNull(resBundle, "testGetLocStringMultipleDifferentCalls")) return;

	getLocStringSingleTest(resBundle, "Select a question", "Frage auswählen", "testGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleTest(resBundle, "Enter password", "Enter password", "Enter password",
			"testGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
			"testGetLocStringMultipleDifferentCalls");
	getLocStringSingleTest(resBundle, "enter password...", "Kennwort eingeben…",
			"testGetLocStringMultipleDifferentCalls");
	getLocStringSingleTest(resBundle, "Backup server unavailable", "Sicherungsserver nicht verfügbar",
			"testGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleTest(resBundle, "Backup server unavailable", "Help", "Sicherungsserver nicht verfügbar",
			"testGetLocStringMultipleDifferentCalls");
	getLocStringSingleTest(resBundle, "Don't Update", "Nicht aktualisieren", "testGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleTest(resBundle, "don't", "Don't Update", "Don't Update", "testGetLocStringMultipleDifferentCalls");
	getLocStringSingleTest(resBundle, "enter password...", "Kennwort eingeben…",
			"testGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleTest(resBundle, "We will send your confirmation email as soon as you have an internet connection.",
			"..............", "Sie erhalten eine Bestätigungs-E-Mail, sobald eine Internetverbindung hergestellt ist.",
			"testGetLocStringMultipleDifferentCalls");
	getLocStringWithKeySingleTest(resBundle, "enter password...", "Enter password", "Kennwort eingeben…",
				"testGetLocStringMultipleDifferentCalls");

	delete resBundle;
}

void runTestResBundle(int* testsNumber, int* failuresNumber) {
	cout << "Running TestResBundle file" << endl;
	cout << "-------------------------------------------------------------" << endl;

	clock_t begin, end, tmp;
	double timeElapsed = .0000;
	short tests_count = 0;

	tmp = clock();
	begin = tmp;
	testResBundleFilePathConstructor();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testResBundleFilePathConstructor took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testResBundleFileAndPathConstructor();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testResBundleFileAndPathConstructor took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testEmptyLocale();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testEmptyLocale took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testContainsSourceTrue();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testContainsSourceTrue took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testContainsSourceFalse();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testContainsSourceFalse took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocString1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocString1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetPseudoString1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetPseudoString1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetPseudoString2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetPseudoString2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetPseudoString3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetPseudoString3 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetPseudoString4();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetPseudoString4 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocString2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocString2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocString3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocString3 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringResBundleFileAndPathConstructor();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringResBundleFileAndPathConstructor took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringWithExistedKey1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringWithExistedKey1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringWithExistedKey2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringWithExistedKey2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringWithNonExistedKey1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringWithNonExistedKey1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringWithNonExistedKey2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringWithNonExistedKey2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocaleWithResourcesGerman();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocaleWithResourcesGerman took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocaleWithResourcesMongolian();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocaleWithResourcesMongolian took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringMultipleTimes();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringMultipleTimes took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringMultipleTimesCrissCross();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringMultipleTimesCrissCross took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringMultipleSameCallsInTime();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringMultipleSameCallsInTime took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringMultipleCrissCrossWithKeys();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringMultipleCrissCrossWithKeys took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringMultipleSameCallsInTimeWithKeys();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringMultipleSameCallsInTimeWithKeys took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetMultipleResourceBundles();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetMultipleResourceBundles took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testGetLocStringMultipleDifferentCalls();
	end = clock();
	timeElapsed = ((double)(end - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testGetLocStringMultipleDifferentCalls took " << timeElapsed << " seconds" << endl;
	tests_count++;


	*testsNumber += tests_count;
	*failuresNumber += resBundleTestFailures;
	cout << "Tests run: "<< tests_count << " , Failures: " << resBundleTestFailures << ", Time elapsed: " << ((double)(end- begin)/CLOCKS_PER_SEC) << " sec" << endl;
	cout << "---------------------- Standard Output ----------------------" << endl;
}
