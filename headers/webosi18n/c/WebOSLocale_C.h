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
 * WebOSLocale_C.h
 *
 * @author Oleksandr Gorbunov
 */

#ifndef WEBOSLOCALE_C_H_
#define WEBOSLOCALE_C_H_

#include <stdbool.h>
/**
 * C Wrapper for webOSLocale class
 *
 * @see for more information go to webOSLocale.h
 */
struct WebOSLocaleC;
typedef struct WebOSLocaleC WebOSLocaleC;

WebOSLocaleC * webOSLocale_create(const char * locale);
WebOSLocaleC * webOSLocale_createByParts(const char * language, const char * region, const char * script, const char * variant);
void webOSLocale_destroy(WebOSLocaleC * webOSLocale);

const char* webOSLocale_GetLanguage(WebOSLocaleC * webOSLocale);
const char* webOSLocale_GetScript(WebOSLocaleC * webOSLocale);
const char* webOSLocale_GetRegion(WebOSLocaleC * webOSLocale);
const char* webOSLocale_GetVariant(WebOSLocaleC * webOSLocale);
const char* webOSLocale_ToString(WebOSLocaleC * webOSLocale);
bool webOSLocale_IsPseudo(WebOSLocaleC * webOSLocale);
bool webOSLocale_EqualsString(WebOSLocaleC * currentLocale, const char * locale);
bool webOSLocale_EqualsObject(WebOSLocaleC * inputLocale, WebOSLocaleC* comparable);
bool webOSLocale_IsCompatibleWith(WebOSLocaleC * inputLocale, WebOSLocaleC* comparable);

#endif /* WEBOSLOCALE_C_H_ */
