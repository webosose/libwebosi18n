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
 * IString_C.h
 * @author Oleksandr Gorbunov
 *
 */
#ifndef ISTRING_C_H_
#define ISTRING_C_H_

#include "webosi18n/c/StringMap_C.h"
#include <stdbool.h>
#include <string.h>
#include <pbnjson.h>
/**
 * C Wrapper for IString class
 *
 * @see for more information go to ResiString.h
 */
struct IStringC;
typedef struct IStringC IStringC;

IStringC* IString_create(const char * text);
void IString_destroy(IStringC * iString);

const char* IString_format(IStringC * iString, StringMap* values);
//const char* IString_formatJSON(IStringC * iString, jvalue_ref values);

const char* IString_formatChoiceBoolRef(IStringC * iString, bool reference, StringMap* values);
const char* IString_formatChoiceStringRef(IStringC * iString, const char * reference, StringMap* values);
const char* IString_formatChoiceDoubleRef(IStringC * iString, double reference, StringMap* values);
//const char* IString_formatChoiceJSONBoolRef(IStringC * iString, bool reference, jvalue_ref values);
//const char* IString_formatChoiceJSONDoubleRef(IStringC * iString, double reference, jvalue_ref values);
//const char* IString_formatChoiceJSONStringRef(IStringC * iString, const char * reference, jvalue_ref* values);

int IString_length(IStringC * iString);
const char* IString_toString(IStringC * iString);

const char* IString_formatChoiceLongStatic(const char * message, const long reference);
const char* IString_formatChoiceDoubleStatic(const char * message, const double reference);
const char* IString_formatWithValuesStatic(const char * message, StringMap* values);
const char* IString_formatChoiceLongWithValuesStatic(const char * message, long reference, StringMap* values);
const char* IString_formatChoiceDoubleWithValuesStatic(const char * message, double reference, StringMap* values);

#endif /* ISTRING_C_H_ */
