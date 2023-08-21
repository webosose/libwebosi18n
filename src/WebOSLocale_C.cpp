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
 * WebOSLocale_C.cpp
 *
 * @author Oleksandr Gorbunov
 */
#include "webosi18n/cxx/WebOSLocale.h"
#include <string.h>

extern "C" {
  #include "webosi18n/c/WebOSLocale_C.h"
}

WebOSLocaleC * webOSLocale_create(const char * locale)
{
	return reinterpret_cast<WebOSLocaleC*>( new WebOSLocale(locale) );
}
WebOSLocaleC * webOSLocale_createByParts(const char * language, const char * region, const char * script, const char * variant)
{
	return reinterpret_cast<WebOSLocaleC*>( new WebOSLocale(language, region, script, variant) );
}
void webOSLocale_destroy(WebOSLocaleC * webOSLocale)
{
	delete reinterpret_cast<WebOSLocale*>(webOSLocale);
}

const char* webOSLocale_GetLanguage(WebOSLocaleC * webOSLocale)
{
	return strdup(reinterpret_cast<WebOSLocale*>(webOSLocale)->getLanguage().c_str());
}
const char* webOSLocale_GetScript(WebOSLocaleC * webOSLocale)
{
	return strdup(reinterpret_cast<WebOSLocale*>(webOSLocale)->getScript().c_str() );
}
const char* webOSLocale_GetRegion(WebOSLocaleC * webOSLocale)
{
	return strdup( reinterpret_cast<WebOSLocale*>(webOSLocale)->getRegion().c_str() );
}
const char* webOSLocale_GetVariant(WebOSLocaleC * webOSLocale)
{
	return strdup( reinterpret_cast<WebOSLocale*>(webOSLocale)->getVariant().c_str() );
}
const char* webOSLocale_ToString(WebOSLocaleC * webOSLocale)
{
	return strdup( reinterpret_cast<WebOSLocale*>(webOSLocale)->toString().c_str() );
}

bool webOSLocale_IsPseudo(WebOSLocaleC * webOSLocale)
{
	return reinterpret_cast<WebOSLocale*>(webOSLocale)->isPseudo();
}
bool webOSLocale_EqualsString(WebOSLocaleC * currentLocale, const char * locale)
{
	return reinterpret_cast<WebOSLocale*>(currentLocale)->equals(locale);
}
bool webOSLocale_EqualsObject(WebOSLocaleC * inputLocale, WebOSLocaleC* comparable)
{
	return reinterpret_cast<WebOSLocale*>(inputLocale)->equals(reinterpret_cast<WebOSLocale*>(comparable));
}
bool webOSLocale_IsCompatibleWith(WebOSLocaleC * inputLocale, WebOSLocaleC* comparable)
{
	return reinterpret_cast<WebOSLocale*>(inputLocale)->isCompatibleWith(reinterpret_cast<WebOSLocale*>(comparable));
}
