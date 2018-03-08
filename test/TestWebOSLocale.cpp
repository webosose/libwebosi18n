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
 * TestWebOSLocale.cpp
 *
 * @author Oleksandr Gorbunov
 */

#include "webosi18n/cxx/WebOSLocale.h"
#include "TestWebOSLocale.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/*
 * Simple C++ Test Suite for WebOSLocale
 */
size_t webOSLocaleTestFailures = 0;

bool assertNotNull(WebOSLocale* locale, string methodName) {
	if (!locale) {
		cout << "\n%TEST_FAILED% testname = " << methodName << " TestWebOSLocale WebOSLocale is NULL" << endl;
		webOSLocaleTestFailures++;
		return false;
	}
	return true;
}

void assertEquals(string current, string expected, string method_name) {
	if (expected.compare(current) != 0) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestResBundle message=error" << endl;
		cout << "		Expetcted: " << expected << ", actual: " << current << endl;
		webOSLocaleTestFailures++;
	}
}

void assertTrue(bool value, string method_name) {
	if (!value) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestResBundle message=error" << endl;
		cout << "		Expetcted value: true " << endl;
		webOSLocaleTestFailures++;
	}
}

void assertFalse(bool value, string method_name) {
	if (value) {
		cout << "\n%TEST_FAILED% testname = " << method_name << " TestResBundle message=error" << endl;
				cout << "		Expetcted value: false " << endl;
		webOSLocaleTestFailures++;
	}
}

void testWebOSLocaleConstructorSpec()
{
	WebOSLocale* loc = new WebOSLocale("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleConstructorSpec")) return;
	delete loc;
}

void testWebOSLocaleConstructorParts()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleConstructorParts")) return;
	delete loc;
}

void testWebOSLocaleGetLanguage()
{
	WebOSLocale* loc = new WebOSLocale("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguage")) return;

	assertEquals(loc->getLanguage(), "en", "testWebOSLocaleGetLanguage");
	delete loc;
}

void testWebOSLocaleGetLanguage2LowerChars()
{
	WebOSLocale* loc = new WebOSLocale("de-AU");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguage")) return;

	assertEquals(loc->getLanguage(), "de", "testWebOSLocaleGetLanguage");
	delete loc;
}

void testWebOSLocaleGetLanguage3LowerChars()
{
	WebOSLocale* loc = new WebOSLocale("ger-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguage")) return;

	assertEquals(loc->getLanguage(), "ger", "testWebOSLocaleGetLanguage");
	delete loc;
}

void testWebOSLocaleGetLanguageNonDigit()
{
	WebOSLocale* loc = new WebOSLocale("ru3-RU");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguage")) return;

	assertEquals(loc->getLanguage(), "", "testWebOSLocaleGetLanguage");
	delete loc;
}

void testWebOSLocaleGetLanguageParts()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageParts")) return;

	assertEquals(loc->getLanguage(), "en", "testWebOSLocaleGetLanguageParts");
	delete loc;
}

void testWebOSLocaleGetRegion()
{
	WebOSLocale* loc = new WebOSLocale("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleGetRegion")) return;

	assertEquals(loc->getRegion(), "US", "testWebOSLocaleGetRegion");
	delete loc;
}

void testWebOSLocaleGetRegionParts()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageParts")) return;

	assertEquals(loc->getRegion(), "US", "testWebOSLocaleGetLanguageParts");
	delete loc;
}

void testWebOSLocaleGetScript()
{
	WebOSLocale* loc = new WebOSLocale("en-US-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleGetScript")) return;

	assertEquals(loc->getScript(), "Latn", "testWebOSLocaleGetScript");
	delete loc;
}

void testWebOSLocaleGetScriptParts()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageParts")) return;

	assertEquals(loc->getScript(), "Latn", "testWebOSLocaleGetLanguageParts");
	delete loc;
}

void testWebOSLocaleGetVariant()
{
	WebOSLocale* loc = new WebOSLocale("en-US-govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetVariant")) return;

	assertEquals(loc->getVariant(), "govnt", "testWebOSLocaleGetVariant");
	delete loc;
}

void testWebOSLocaleGetVariantParts()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetVariantParts")) return;

	assertEquals(loc->getVariant(), "govnt", "testWebOSLocaleGetVariantParts");
	delete loc;
}

void testWebOSLocaleGetOutOfOrder()
{
	WebOSLocale* loc = new WebOSLocale("US-govnt-en-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleGetOutOfOrder")) return;

	assertEquals(loc->getLanguage(), "en", "testWebOSLocaleGetOutOfOrder");
	assertEquals(loc->getScript(), "Latn", "testWebOSLocaleGetOutOfOrder");
	assertEquals(loc->getRegion(), "US", "testWebOSLocaleGetOutOfOrder");
	assertEquals(loc->getVariant(), "govnt", "testWebOSLocaleGetOutOfOrder");
	delete loc;
}

void testWebOSLocaleGetLanguageSpecEmpty()
{
	WebOSLocale* loc = new WebOSLocale("");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageSpecEmpty")) return;

	assertEquals(loc->getLanguage(), "", "testWebOSLocaleGetLanguageSpecEmpty");
	delete loc;
}

void testWebOSLocaleGetRegionSpecEmpty()
{
	WebOSLocale* loc = new WebOSLocale("");
	if (!assertNotNull(loc, "testWebOSLocaleGetRegionSpecEmpty")) return;

	assertEquals(loc->getRegion(), "", "testWebOSLocaleGetRegionSpecEmpty");
	delete loc;
}

void testWebOSLocaleGetScriptSpecEmpty()
{
	WebOSLocale* loc = new WebOSLocale("");
	if (!assertNotNull(loc, "testWebOSLocaleGetScriptSpecEmpty")) return;

	assertEquals(loc->getScript(), "", "testWebOSLocaleGetScriptSpecEmpty");
	delete loc;
}

void testWebOSLocaleGetVariantSpecEmpty()
{
	WebOSLocale* loc = new WebOSLocale("");
	if (!assertNotNull(loc, "testWebOSLocaleGetVariantSpecEmpty")) return;

	assertEquals(loc->getVariant(), "", "testWebOSLocaleGetVariantSpecEmpty");
	delete loc;
}

void testWebOSLocaleGetLanguageSpecMissing()
{
	WebOSLocale* loc = new WebOSLocale("-US-govt");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageSpecMissing")) return;

	assertEquals(loc->getLanguage(), "", "testWebOSLocaleGetLanguageSpecMissing");
	delete loc;
}

void testWebOSLocaleGetRegionSpecMissing()
{
	WebOSLocale* loc = new WebOSLocale("en--govt");
	if (!assertNotNull(loc, "testWebOSLocaleGetRegionSpecMissing")) return;

	assertEquals(loc->getRegion(), "", "testWebOSLocaleGetRegionSpecMissing");
	delete loc;
}

void testWebOSLocaleGetRegionSpecOnlyLang()
{
	WebOSLocale* loc = new WebOSLocale("en");
	if (!assertNotNull(loc, "testWebOSLocaleGetRegionSpecOnlyLang")) return;

	assertEquals(loc->getRegion(), "", "testWebOSLocaleGetRegionSpecOnlyLang");
	delete loc;
}

void testWebOSLocaleGetVariantSpecOnlyLangAndReg()
{
	WebOSLocale* loc = new WebOSLocale("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleGetVariantSpecOnlyLangAndReg")) return;

	assertEquals(loc->getVariant(), "", "testWebOSLocaleGetVariantSpecOnlyLangAndReg");
	delete loc;
}

void testWebOSLocaleGetVariantSpecMissing()
{
	WebOSLocale* loc = new WebOSLocale("en-US-");
	if (!assertNotNull(loc, "testWebOSLocaleGetVariantSpecMissing")) return;

	assertEquals(loc->getVariant(), "", "testWebOSLocaleGetVariantSpecMissing");
	delete loc;
}

void testWebOSLocaleGetLanguageEmptySpecMissing()
{
	WebOSLocale* loc = new WebOSLocale(string());
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageSpecNull")) return;

	assertEquals(loc->getLanguage(), "", "testWebOSLocaleGetLanguageSpecNull");
	delete loc;
}

void testWebOSLocaleGetRegionEmptySpecEmpty()
{
	WebOSLocale* loc = new WebOSLocale(string());
	if (!assertNotNull(loc, "testWebOSLocaleGetRegionEmptySpecEmpty")) return;

	assertEquals(loc->getRegion(), "", "testWebOSLocaleGetRegionEmptySpecEmpty");
	delete loc;
}

void testWebOSLocaleGetVariantEmptySpecEmpty()
{
	WebOSLocale* loc = new WebOSLocale(string());
	if (!assertNotNull(loc, "testWebOSLocaleGetVariantEmptySpecEmpty")) return;

	assertEquals(loc->getVariant(), "", "testWebOSLocaleGetVariantEmptySpecEmpty");
	delete loc;
}

void testWebOSLocaleGetLanguagePartsEmpty()
{
	WebOSLocale* loc = new WebOSLocale(string(), "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguagePartsEmpty")) return;

	assertEquals(loc->getLanguage(), "", "testWebOSLocaleGetLanguagePartsEmpty");
	delete loc;
}

void testWebOSLocaleGetRegionPartsEmpty()
{
	WebOSLocale* loc = new WebOSLocale("en", string(), "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetRegionPartsEmpty")) return;

	assertEquals(loc->getRegion(), "", "testWebOSLocaleGetRegionPartsEmpty");
	delete loc;
}

void testWebOSLocaleGetScriptPartsEmpty()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", string(), "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetScriptPartsEmpty")) return;

	assertEquals(loc->getScript(), "", "testWebOSLocaleGetScriptPartsEmpty");
	delete loc;
}

void testWebOSLocaleGetVariantPartsEmpty()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", string());
	if (!assertNotNull(loc, "testWebOSLocaleGetVariantPartsEmpty")) return;

	assertEquals(loc->getVariant(), "", "testWebOSLocaleGetVariantPartsEmpty");
	delete loc;
}

void testWebOSLocaleGetLanguageOldISOCodes1()
{
	WebOSLocale* loc = new WebOSLocale("he-IL");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageOldISOCodes1")) return;

	assertEquals(loc->getLanguage(), "he", "testWebOSLocaleGetLanguageOldISOCodes1");
	delete loc;
}

void testWebOSLocaleGetLanguageOldISOCodes2()
{
	WebOSLocale* loc = new WebOSLocale("yi");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageOldISOCodes2")) return;

	assertEquals(loc->getLanguage(), "yi", "testWebOSLocaleGetLanguageOldISOCodes2");
	delete loc;
}

void testWebOSLocaleGetLanguageOldISOCodes3()
{
	WebOSLocale* loc = new WebOSLocale("id-ID");
	if (!assertNotNull(loc, "testWebOSLocaleGetLanguageOldISOCodes3")) return;

	assertEquals(loc->getLanguage(), "id", "testWebOSLocaleGetLanguageOldISOCodes3");
	delete loc;
}

void testWebOSLocaleIsPseudoTrue()
{
	WebOSLocale* loc = new WebOSLocale("zxx-XX");
	if (!assertNotNull(loc, "testWebOSLocaleIsPseudoTrue")) return;

	assertTrue(loc->isPseudo(), "testWebOSLocaleIsPseudoTrue");
	delete loc;
}

void testWebOSLocaleIsPseudoFalse()
{
	WebOSLocale* loc = new WebOSLocale("uk-UA");
	if (!assertNotNull(loc, "testWebOSLocaleIsPseudoFalse")) return;

	assertFalse(loc->isPseudo(), "testWebOSLocaleIsPseudoFalse");
	delete loc;
}

void testWebOSLocaleGetSpec()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetSpec")) return;

	assertEquals(loc->toString(), "en-Latn-US-govnt", "testWebOSLocaleGetSpec");
	delete loc;
}

void testWebOSLocaleGetSpecPartsMissing()
{
	WebOSLocale* loc = new WebOSLocale("en", string(), "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleGetSpecPartsMissing")) return;

	assertEquals(loc->toString(), "en-Latn-govnt", "testWebOSLocaleGetSpecPartsMissing");
	delete loc;
}

void testWebOSLocaleGetSpecNoVariant()
{
	WebOSLocale* loc = new WebOSLocale("en", "US", "Latn", string());
	if (!assertNotNull(loc, "testWebOSLocaleGetSpecNoVariant")) return;

	assertEquals(loc->toString(), "en-Latn-US", "testWebOSLocaleGetSpecNoVariant");
	delete loc;
}

void testWebOSLocaleGetSpecRearrange()
{
	WebOSLocale* loc = new WebOSLocale("US-en-GOVERNMT-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleGetSpecRearrange")) return;

	assertEquals(loc->toString(), "en-Latn-US-GOVERNMT", "testWebOSLocaleGetSpecRearrange");
	delete loc;
}

void testWebOSLocaleEquals()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-Latn-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleEquals")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleEquals")) return;

	assertTrue(loc1->equals(loc2), "testWebOSLocaleEquals");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleEqualsSymmetric()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-Latn-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleEqualsSymmetric")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleEqualsSymmetric")) return;

	assertTrue(loc2->equals(loc1), "testWebOSLocaleEqualsSymmetric");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleNotEquals()
{
	WebOSLocale* loc1 = new WebOSLocale("de-DE");
	WebOSLocale* loc2 = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleNotEquals")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleNotEquals")) return;

	assertFalse(loc1->equals(loc2), "testWebOSLocaleEqualsSymmetric");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleNotEqualsClose()
{
	WebOSLocale* loc1 = new WebOSLocale("de-DE-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleNotEqualsClose")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleNotEqualsClose")) return;

	assertFalse(loc1->equals(loc2), "testWebOSLocaleNotEqualsClose");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleEqualsNull()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-govnt");
	WebOSLocale* loc2 = NULL;
	if (!assertNotNull(loc1, "testWebOSLocaleEqualsNull")) return;

	assertFalse(loc1->equals(loc2), "testWebOSLocaleEqualsNull");
	delete loc1;
	delete loc2;
}




void testWebOSLocaleEqualsMissingParts()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en", "US", string(), string());
	if (!assertNotNull(loc1, "testWebOSLocaleEqualsMissingParts")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleEqualsMissingParts")) return;

	assertFalse(loc1->equals(loc2), "testWebOSLocaleEqualsMissingParts");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleEqualsBothMissingParts()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US");
	WebOSLocale* loc2 = new WebOSLocale("en", "US", string(), string());
	if (!assertNotNull(loc1, "testWebOSLocaleEqualsBothMissingParts")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleEqualsBothMissingParts")) return;

	assertTrue(loc1->equals(loc2), "testWebOSLocaleEqualsBothMissingParts");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithSelf()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithSelf")) return;

	assertTrue(loc1->isCompatibleWith(loc1), "testWebOSLocaleIsCompatibleWithSelf");
	delete loc1;
}

void testWebOSLocaleIsCompatibleWithEqual()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US");
	WebOSLocale* loc2 = new WebOSLocale("en-US");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithEqual")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithEqual")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithEqual");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithParentWithRegion()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en-US");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithParentWithRegion")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithParentWithRegion")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithParentWithRegion");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithParentWithLanguage()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US");
	WebOSLocale* loc2 = new WebOSLocale("en");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithParentWithLanguage")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithParentWithLanguage")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithParentWithLanguage");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithParentWithRoot()
{
	WebOSLocale* loc1 = new WebOSLocale("en");
	WebOSLocale* loc2 = new WebOSLocale("");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithParentWithRoot")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithParentWithRoot")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithParentWithRoot");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithGrandFather()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithGrandFather")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithGrandFather")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithGrandFather");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithGreatGrandFather2()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-Latn-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithGreatGrandFather2")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithGreatGrandFather2")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithGreatGrandFather2");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithGreatGrandFather()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-govnt");
	WebOSLocale* loc2 = new WebOSLocale("");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithGreatGrandFather")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithGreatGrandFather")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithGreatGrandFather");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithGrandFather3()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US");
	WebOSLocale* loc2 = new WebOSLocale("");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithGrandFather3")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithGrandFather3")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithGrandFather3");
	delete loc1;
	delete loc2;
}

void testWebOSLocaleIsCompatibleWithCousinVariant()
{
	WebOSLocale* loc1 = new WebOSLocale("en-US-govnt");
	WebOSLocale* loc2 = new WebOSLocale("en-US-SCIENTIF");
	if (!assertNotNull(loc1, "testWebOSLocaleIsCompatibleWithCousinVariant")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleIsCompatibleWithCousinVariant")) return;

	assertTrue(loc1->isCompatibleWith(loc2), "testWebOSLocaleIsCompatibleWithCousinVariant");
	delete loc1;
	delete loc2;
}

void runTestWebOSLocale(int* testsNumber, int* failuresNumber)
{
	cout << "\nRunning TestWebOSLocale file" << endl;
	cout << "-------------------------------------------------------------" << endl;

	clock_t begin, end, tmp;
	double timeElapsed = .0000;
	short tests_count = 0;

	tmp = clock();
	begin = tmp;
	testWebOSLocaleConstructorSpec();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleConstructorSpec took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleConstructorParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleConstructorParts took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguage();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguage took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguage2LowerChars();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguage2LowerChars took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguage3LowerChars();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguage3LowerChars took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageNonDigit();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageNonDigit took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageParts took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetRegion();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetRegion took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetRegionParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetRegionParts took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetScript();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetScript took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetScriptParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetScriptParts took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetVariant();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetVariant took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetVariantParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetVariantParts took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetOutOfOrder();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetOutOfOrder took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageSpecEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetRegionSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetRegionSpecEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetScriptSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetScriptSpecEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetVariantSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetVariantSpecEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageSpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageSpecMissing took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetRegionSpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetRegionSpecMissing took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetRegionSpecOnlyLang();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetRegionSpecOnlyLang took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetVariantSpecOnlyLangAndReg();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetVariantSpecOnlyLangAndReg took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetVariantSpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetVariantSpecMissing took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageEmptySpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageEmptySpecMissing took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetRegionEmptySpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetRegionEmptySpecEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetVariantEmptySpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetVariantEmptySpecEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguagePartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguagePartsEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetRegionPartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetRegionPartsEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetScriptPartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetScriptPartsEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetVariantPartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetVariantPartsEmpty took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageOldISOCodes1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageOldISOCodes1 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageOldISOCodes2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageOldISOCodes2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetLanguageOldISOCodes3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetLanguageOldISOCodes3 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsPseudoTrue();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsPseudoTrue took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsPseudoFalse();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsPseudoFalse took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetSpec();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetSpec took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetSpecPartsMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetSpecPartsMissing took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetSpecNoVariant();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetSpecNoVariant took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleGetSpecRearrange();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleGetSpecRearrange took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleEquals();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleEquals took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleEqualsSymmetric();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleEqualsSymmetric took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleNotEquals();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleNotEquals took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleNotEqualsClose();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleNotEqualsClose took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleEqualsNull();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleEqualsNull took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleEqualsMissingParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleEqualsMissingParts took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleEqualsBothMissingParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleEqualsBothMissingParts took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithSelf();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithSelf took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithEqual took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithParentWithLanguage();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithParentWithLanguage took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithParentWithRegion();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithParentWithRegion took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithParentWithRoot();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithParentWithRoot took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithGrandFather();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithGrandFather took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithGreatGrandFather();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithGreatGrandFather took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithGreatGrandFather2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithGreatGrandFather2 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithGrandFather3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithGrandFather3 took " << timeElapsed << " seconds" << endl;
	tests_count++;

	tmp = clock();
	testWebOSLocaleIsCompatibleWithCousinVariant();
	end = clock();
	timeElapsed = ((double)(end - tmp))/CLOCKS_PER_SEC;
	cout << "Testcase: testWebOSLocaleIsCompatibleWithCousinVariant took " << timeElapsed << " seconds" << endl;
	tests_count++;

	*testsNumber += tests_count;
	*failuresNumber += webOSLocaleTestFailures;
	cout << "Tests run: "<< tests_count << " , Failures: " << webOSLocaleTestFailures << ", Time elapsed: " << ((double)(end- begin)/CLOCKS_PER_SEC) << " sec" << endl;
	cout << "---------------------- Standard Output ----------------------" << endl;
}
