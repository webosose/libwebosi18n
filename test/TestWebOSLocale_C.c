// Copyright (c) 2013-2022 LG Electronics, Inc.
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
 * TestWebOSLocale_C.c
 *
 *  Created on: Oct 29, 2013
 *      Author: oleksandr.gorbunov
 */
#include "TestWebOSLocale_C.h"
#include "webosi18n/c/WebOSLocale_C.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

size_t webosC_failures_count = 0;

bool assertNotNull(WebOSLocaleC* locale, const char* methodName) {
	if (!locale) {
		printf("\nTEST_FAILED testname = %s TestWebOSLocale_C locale is NULL\n", methodName);
		webosC_failures_count++;
		return false;
	}
	return true;
}

void assertEquals(const char* current, const char* expected, const char* method_name) {
	if (strcmp(expected, current) != 0) {
		printf("\nTEST_FAILED testname = %s TestWebOSLocale_C locale is NULL\n", method_name);
		printf("\n            Expetcted = %s, actual: %s\n", expected, current);
		webosC_failures_count++;
	}
}

void assertTrue(bool value, const char* method_name) {
	if (!value) {
		printf("\nTEST_FAILED testname = %s TestWebOSLocale_C locale is NULL\n", method_name);
		printf("\n            Expetcted value: true\n");
		webosC_failures_count++;
	}
}

void assertFalse(bool value, const char* method_name) {
	if (value) {
		printf("\nTEST_FAILED testname = %s TestWebOSLocale_C locale is NULL\n", method_name);
		printf("\n            Expetcted value: false\n");
		webosC_failures_count++;
	}
}

void testWebOSLocaleCConstructorSpec()
{
	WebOSLocaleC* loc = webOSLocale_create("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleCConstructorSpec")) return;
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCConstructorParts()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCConstructorParts")) return;
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguage()
{
	WebOSLocaleC* loc = webOSLocale_create("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguage")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "en", "testWebOSLocaleCGetLanguage");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguage2LowerChars()
{
	WebOSLocaleC* loc = webOSLocale_create("de-AU");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguage2LowerChars")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "de", "testWebOSLocaleCGetLanguage2LowerChars");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguage3LowerChars()
{
	WebOSLocaleC* loc = webOSLocale_create("ger-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguage3LowerChars")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "ger", "testWebOSLocaleCGetLanguage3LowerChars");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageNonDigit()
{
	WebOSLocaleC* loc = webOSLocale_create("ru3-RU");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguage")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "", "testWebOSLocaleCGetLanguage");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageParts()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageParts")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "en", "testWebOSLocaleCGetLanguageParts");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetRegion()
{
	WebOSLocaleC* loc = webOSLocale_create("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleCGetRegion")) return;

	assertEquals(webOSLocale_GetRegion(loc), "US", "testWebOSLocaleCGetRegion");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetRegionParts()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageParts")) return;

	assertEquals(webOSLocale_GetRegion(loc), "US", "testWebOSLocaleCGetLanguageParts");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetScript()
{
	WebOSLocaleC* loc = webOSLocale_create("en-US-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleCGetScript")) return;

	assertEquals(webOSLocale_GetScript(loc), "Latn", "testWebOSLocaleCGetScript");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetScriptParts()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageParts")) return;

	assertEquals(webOSLocale_GetScript(loc), "Latn", "testWebOSLocaleCGetLanguageParts");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetVariant()
{
	WebOSLocaleC* loc = webOSLocale_create("en-US-govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetVariant")) return;

	assertEquals(webOSLocale_GetVariant(loc), "govnt", "testWebOSLocaleCGetVariant");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetVariantParts()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetVariantParts")) return;

	assertEquals(webOSLocale_GetVariant(loc), "govnt", "testWebOSLocaleCGetVariantParts");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetOutOfOrder()
{
	WebOSLocaleC* loc = webOSLocale_create("US-govnt-en-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleCGetOutOfOrder")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "en", "testWebOSLocaleCGetOutOfOrder");
	assertEquals(webOSLocale_GetScript(loc), "Latn", "testWebOSLocaleCGetOutOfOrder");
	assertEquals(webOSLocale_GetRegion(loc), "US", "testWebOSLocaleCGetOutOfOrder");
	assertEquals(webOSLocale_GetVariant(loc), "govnt", "testWebOSLocaleCGetOutOfOrder");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageSpecEmpty()
{
	WebOSLocaleC* loc = webOSLocale_create("");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageSpecEmpty")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "", "testWebOSLocaleCGetLanguageSpecEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetRegionSpecEmpty()
{
	WebOSLocaleC* loc = webOSLocale_create("");
	if (!assertNotNull(loc, "testWebOSLocaleCGetRegionSpecEmpty")) return;

	assertEquals(webOSLocale_GetRegion(loc), "", "testWebOSLocaleCGetRegionSpecEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetScriptSpecEmpty()
{
	WebOSLocaleC* loc = webOSLocale_create("");
	if (!assertNotNull(loc, "testWebOSLocaleCGetScriptSpecEmpty")) return;

	assertEquals(webOSLocale_GetScript(loc), "", "testWebOSLocaleCGetScriptSpecEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetVariantSpecEmpty()
{
	WebOSLocaleC* loc = webOSLocale_create("");
	if (!assertNotNull(loc, "testWebOSLocaleCGetVariantSpecEmpty")) return;

	assertEquals(webOSLocale_GetVariant(loc), "", "testWebOSLocaleCGetVariantSpecEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageSpecMissing()
{
	WebOSLocaleC* loc = webOSLocale_create("-US-govt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageSpecMissing")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "", "testWebOSLocaleCGetLanguageSpecMissing");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetRegionSpecMissing()
{
	WebOSLocaleC* loc = webOSLocale_create("en--govt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetRegionSpecMissing")) return;

	assertEquals(webOSLocale_GetRegion(loc), "", "testWebOSLocaleCGetRegionSpecMissing");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetRegionSpecOnlyLang()
{
	WebOSLocaleC* loc = webOSLocale_create("en");
	if (!assertNotNull(loc, "testWebOSLocaleCGetRegionSpecOnlyLang")) return;

	assertEquals(webOSLocale_GetRegion(loc), "", "testWebOSLocaleCGetRegionSpecOnlyLang");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetVariantSpecOnlyLangAndReg()
{
	WebOSLocaleC* loc = webOSLocale_create("en-US");
	if (!assertNotNull(loc, "testWebOSLocaleCGetVariantSpecOnlyLangAndReg")) return;

	assertEquals(webOSLocale_GetVariant(loc), "", "testWebOSLocaleCGetVariantSpecOnlyLangAndReg");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetVariantSpecMissing()
{
	WebOSLocaleC* loc = webOSLocale_create("en-US-");
	if (!assertNotNull(loc, "testWebOSLocaleCGetVariantSpecMissing")) return;

	assertEquals(webOSLocale_GetVariant(loc), "", "testWebOSLocaleCGetVariantSpecMissing");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageEmptySpecMissing()
{
	WebOSLocaleC* loc = webOSLocale_create("");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageSpecNull")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "", "testWebOSLocaleCGetLanguageSpecNull");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetRegionEmptySpecEmpty()
{
	WebOSLocaleC* loc = webOSLocale_create("");
	if (!assertNotNull(loc, "testWebOSLocaleCGetRegionEmptySpecEmpty")) return;

	assertEquals(webOSLocale_GetRegion(loc), "", "testWebOSLocaleCGetRegionEmptySpecEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetVariantEmptySpecEmpty()
{
	WebOSLocaleC* loc = webOSLocale_create("");
	if (!assertNotNull(loc, "testWebOSLocaleCGetVariantEmptySpecEmpty")) return;

	assertEquals(webOSLocale_GetVariant(loc), "", "testWebOSLocaleCGetVariantEmptySpecEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguagePartsEmpty()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguagePartsEmpty")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "", "testWebOSLocaleCGetLanguagePartsEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetRegionPartsEmpty()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetRegionPartsEmpty")) return;

	assertEquals(webOSLocale_GetRegion(loc), "", "testWebOSLocaleCGetRegionPartsEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetScriptPartsEmpty()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetScriptPartsEmpty")) return;

	assertEquals(webOSLocale_GetScript(loc), "", "testWebOSLocaleCGetScriptPartsEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetVariantPartsEmpty()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "");
	if (!assertNotNull(loc, "testWebOSLocaleCGetVariantPartsEmpty")) return;

	assertEquals(webOSLocale_GetVariant(loc), "", "testWebOSLocaleCGetVariantPartsEmpty");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageOldISOCodes1()
{
	WebOSLocaleC* loc = webOSLocale_create("he-IL");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageOldISOCodes1")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "he", "testWebOSLocaleCGetLanguageOldISOCodes1");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageOldISOCodes2()
{
	WebOSLocaleC* loc = webOSLocale_create("yi");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageOldISOCodes2")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "yi", "testWebOSLocaleCGetLanguageOldISOCodes2");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetLanguageOldISOCodes3()
{
	WebOSLocaleC* loc = webOSLocale_create("id-ID");
	if (!assertNotNull(loc, "testWebOSLocaleCGetLanguageOldISOCodes3")) return;

	assertEquals(webOSLocale_GetLanguage(loc), "id", "testWebOSLocaleCGetLanguageOldISOCodes3");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCIsPseudoTrue()
{
	WebOSLocaleC* loc = webOSLocale_create("zxx-XX");
	if (!assertNotNull(loc, "testWebOSLocaleCIsPseudoTrue")) return;

	assertTrue(webOSLocale_IsPseudo(loc), "testWebOSLocaleCIsPseudoTrue");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCIsPseudoFalse()
{
	WebOSLocaleC* loc = webOSLocale_create("uk-UA");
	if (!assertNotNull(loc, "testWebOSLocaleCIsPseudoFalse")) return;

	assertFalse(webOSLocale_IsPseudo(loc), "testWebOSLocaleCIsPseudoFalse");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetSpec()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetSpec")) return;

	assertEquals(webOSLocale_ToString(loc), "en-Latn-US-govnt", "testWebOSLocaleCGetSpec");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetSpecPartsMissing()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "", "Latn", "govnt");
	if (!assertNotNull(loc, "testWebOSLocaleCGetSpecPartsMissing")) return;

	assertEquals(webOSLocale_ToString(loc), "en-Latn-govnt", "testWebOSLocaleCGetSpecPartsMissing");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetSpecNoVariant()
{
	WebOSLocaleC* loc = webOSLocale_createByParts("en", "US", "Latn", "");
	if (!assertNotNull(loc, "testWebOSLocaleCGetSpecNoVariant")) return;

	assertEquals(webOSLocale_ToString(loc), "en-Latn-US", "testWebOSLocaleCGetSpecNoVariant");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCGetSpecRearrange()
{
	WebOSLocaleC* loc = webOSLocale_create("US-en-GOVERNMT-Latn");
	if (!assertNotNull(loc, "testWebOSLocaleCGetSpecRearrange")) return;

	assertEquals(webOSLocale_ToString(loc), "en-Latn-US-GOVERNMT", "testWebOSLocaleCGetSpecRearrange");
	webOSLocale_destroy(loc);
}

void testWebOSLocaleCEquals()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-Latn-govnt");
	WebOSLocaleC* loc2 = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleCEquals")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCEquals")) return;

	assertTrue(webOSLocale_EqualsObject(loc1, loc2), "testWebOSLocaleCEquals");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCEqualsSymmetric()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-Latn-govnt");
	WebOSLocaleC* loc2 = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleCEqualsSymmetric")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCEqualsSymmetric")) return;

	assertTrue(webOSLocale_EqualsObject(loc2, loc1), "testWebOSLocaleCEqualsSymmetric");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCNotEquals()
{
	WebOSLocaleC* loc1 = webOSLocale_create("de-DE");
	WebOSLocaleC* loc2 = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleCNotEquals")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCNotEquals")) return;

	assertFalse(webOSLocale_EqualsObject(loc1, loc2), "testWebOSLocaleCEqualsSymmetric");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCNotEqualsClose()
{
	WebOSLocaleC* loc1 = webOSLocale_create("de-DE-govnt");
	WebOSLocaleC* loc2 = webOSLocale_createByParts("en", "US", "Latn", "govnt");
	if (!assertNotNull(loc1, "testWebOSLocaleCNotEqualsClose")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCNotEqualsClose")) return;

	assertFalse(webOSLocale_EqualsObject(loc1, loc2), "testWebOSLocaleCNotEqualsClose");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCEqualsNull()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-govnt");
	WebOSLocaleC* loc2 = NULL;
	if (!assertNotNull(loc1, "testWebOSLocaleCEqualsNull")) return;

	assertFalse(webOSLocale_EqualsObject(loc1, loc2), "testWebOSLocaleCEqualsNull");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCEqualsMissingParts()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-govnt");
	WebOSLocaleC* loc2 = webOSLocale_createByParts("en", "US", "", "");
	if (!assertNotNull(loc1, "testWebOSLocaleCEqualsMissingParts")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCEqualsMissingParts")) return;

	assertFalse(webOSLocale_EqualsObject(loc1, loc2), "testWebOSLocaleCEqualsMissingParts");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCEqualsBothMissingParts()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US");
	WebOSLocaleC* loc2 = webOSLocale_createByParts("en", "US", "", "");
	if (!assertNotNull(loc1, "testWebOSLocaleCEqualsBothMissingParts")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCEqualsBothMissingParts")) return;

	assertTrue(webOSLocale_EqualsObject(loc1, loc2), "testWebOSLocaleCEqualsBothMissingParts");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithSelf()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithSelf")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc1), "testWebOSLocaleCIsCompatibleWithSelf");
	webOSLocale_destroy(loc1);
}

void testWebOSLocaleCIsCompatibleWithEqual()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US");
	WebOSLocaleC* loc2 = webOSLocale_create("en-US");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithEqual")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithEqual")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithEqual");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithParentWithRegion()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-govnt");
	WebOSLocaleC* loc2 = webOSLocale_create("en-US");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithParentWithRegion")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithParentWithRegion")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithParentWithRegion");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithParentWithLanguage()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US");
	WebOSLocaleC* loc2 = webOSLocale_create("en");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithParentWithLanguage")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithParentWithLanguage")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithParentWithLanguage");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithParentWithRoot()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en");
	WebOSLocaleC* loc2 = webOSLocale_create("");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithParentWithRoot")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithParentWithRoot")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithParentWithRoot");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithGrandFather()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-govnt");
	WebOSLocaleC* loc2 = webOSLocale_create("en");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithGrandFather")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithGrandFather")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithGrandFather");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithGreatGrandFather2()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-Latn-govnt");
	WebOSLocaleC* loc2 = webOSLocale_create("en");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithGreatGrandFather2")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithGreatGrandFather2")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithGreatGrandFather2");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithGreatGrandFather()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-govnt");
	WebOSLocaleC* loc2 = webOSLocale_create("");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithGreatGrandFather")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithGreatGrandFather")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithGreatGrandFather");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithGrandFather3()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US");
	WebOSLocaleC* loc2 = webOSLocale_create("");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithGrandFather3")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithGrandFather3")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithGrandFather3");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void testWebOSLocaleCIsCompatibleWithCousinVariant()
{
	WebOSLocaleC* loc1 = webOSLocale_create("en-US-govnt");
	WebOSLocaleC* loc2 = webOSLocale_create("en-US-SCIENTIF");
	if (!assertNotNull(loc1, "testWebOSLocaleCIsCompatibleWithCousinVariant")) return;
	if (!assertNotNull(loc2, "testWebOSLocaleCIsCompatibleWithCousinVariant")) return;

	assertTrue(webOSLocale_IsCompatibleWith(loc1, loc2), "testWebOSLocaleCIsCompatibleWithCousinVariant");
	webOSLocale_destroy(loc1);
	webOSLocale_destroy(loc2);
}

void runTestWebOSLocale_C(int* testsNumber, int* failuresNumber)
{
	printf("\nRunning TestWebOSLocale_C file\n");

	clock_t begin, end, tmp;
	double timeElapsed = .0000;
	short tests_count = 0;

	tmp = clock();
	begin = tmp;
	testWebOSLocaleCConstructorSpec();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCConstructorSpec took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCConstructorParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCConstructorParts took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguage();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguage took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguage2LowerChars();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguage2LowerChars took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguage3LowerChars();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguage3LowerChars took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageNonDigit();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageNonDigit took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageParts took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetRegion();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetRegion took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetRegionParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageParts took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetScript();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetScript took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetScriptParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetScriptParts took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetVariant();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetVariant took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetVariantParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetVariantParts took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetOutOfOrder();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetOutOfOrder took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageSpecEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetRegionSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetRegionSpecEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetScriptSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetScriptSpecEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetVariantSpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetVariantSpecEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageSpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageSpecMissing took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetRegionSpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetRegionSpecMissing took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetRegionSpecOnlyLang();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetRegionSpecOnlyLang took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetVariantSpecOnlyLangAndReg();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetVariantSpecOnlyLangAndReg took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetVariantSpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetVariantSpecMissing took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageEmptySpecMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageEmptySpecMissing took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetRegionEmptySpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetRegionEmptySpecEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetVariantEmptySpecEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetVariantEmptySpecEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguagePartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguagePartsEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetRegionPartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetRegionPartsEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetScriptPartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetScriptPartsEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetVariantPartsEmpty();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetVariantPartsEmpty took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageOldISOCodes1();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageOldISOCodes1 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageOldISOCodes2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageOldISOCodes2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetLanguageOldISOCodes3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetLanguageOldISOCodes3 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsPseudoTrue();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsPseudoTrue took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsPseudoFalse();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsPseudoFalse took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetSpec();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetSpec took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetSpecPartsMissing();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetSpecPartsMissing took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetSpecNoVariant();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetSpecNoVariant took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCGetSpecRearrange();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCGetSpecRearrange took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCEquals();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCEquals took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCEqualsSymmetric();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCEqualsSymmetric took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCNotEquals();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCNotEquals took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCNotEqualsClose();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCNotEqualsClose took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCEqualsNull();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCEqualsNull took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCEqualsMissingParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCEqualsMissingParts took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCEqualsBothMissingParts();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCEqualsBothMissingParts took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithSelf();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithSelf took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithEqual();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithEqual took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithParentWithRegion();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithParentWithRegion took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithParentWithLanguage();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithParentWithLanguage took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithParentWithRoot();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithParentWithRoot took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithGrandFather();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithGrandFather took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithGreatGrandFather2();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithGreatGrandFather2 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithGreatGrandFather();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithGreatGrandFather took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithGrandFather3();
	timeElapsed = ((double)(clock() - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithGrandFather3 took %f seconds\n", timeElapsed);
	tests_count++;

	tmp = clock();
	testWebOSLocaleCIsCompatibleWithCousinVariant();
	end = clock();
	timeElapsed = ((double)(end - tmp))/CLOCKS_PER_SEC;
	printf("Testcase: testWebOSLocaleCIsCompatibleWithCousinVariant took %f seconds\n", timeElapsed);
	tests_count++;

	*testsNumber += tests_count;
	*failuresNumber += webosC_failures_count;
	printf("Tests run: %i , Failures: %zu, Time elapsed: %f sec\n", tests_count, webosC_failures_count, ((double)(end - begin)/CLOCKS_PER_SEC));
	printf("---------------------- Standard Output ----------------------\n");
}
