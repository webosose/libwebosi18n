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

#include "webosi18n/cxx/IString.h"
#include <map>
#include <string.h>

extern "C" {
  #include "webosi18n/c/IString_C.h"
}

IStringC* IString_create(const char * text)
{
    return reinterpret_cast<IStringC*>( new IString(text) );
}
void IString_destroy(IStringC* iString)
{
	if ( !iString ) return;
	delete reinterpret_cast<IString*>(iString);
}

const char* IString_format(IStringC * iString, StringMap* values)
{
	if ( !iString ) return "";
	std::map<std::string,std::string> STDMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		STDMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));

	const char* result = strdup( reinterpret_cast<IString*>(iString)->format(STDMap).c_str() );
	STDMap.clear();
	return result;
}
/*const char* IString_formatJSON(IStringC * iString, jvalue_ref values)
{
	return static_cast<std::string>(reinterpret_cast<IString*>(iString)->format(values)).c_str();
}*/

const char* IString_formatChoiceBoolRef(IStringC * iString, bool reference, StringMap* values)
{
	if ( !iString ) return "";
	std::map<std::string,std::string> STDMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		STDMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));

	const char* result = strdup( reinterpret_cast<IString*>(iString)->formatChoice(reference, STDMap).c_str() );
	STDMap.clear();
	return result;
}
const char* IString_formatChoiceStringRef(IStringC * iString, const char * reference, StringMap* values)
{
	if ( !iString ) return "";
	std::map<std::string,std::string> STDMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		STDMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));

	const char* result = strdup( reinterpret_cast<IString*>(iString)->formatChoice(string(reference), STDMap).c_str() );
	STDMap.clear();
	return result;
}
const char* IString_formatChoiceDoubleRef(IStringC * iString, double reference, StringMap* values)
{
	if ( !iString ) return "";
	std::map<std::string,std::string> STDMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		STDMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));

	const char* result = strdup( reinterpret_cast<IString*>(iString)->formatChoice(reference, STDMap).c_str() );
	STDMap.clear();
	return result;
}

/*const char* IString_formatChoiceJSONBoolRef(IStringC * iString, bool reference, jvalue_ref values)
{
	return static_cast<std::string>(reinterpret_cast<IString*>(iString)->format(reference, values)).c_str();
}
const char* IString_formatChoiceJSONDoubleRef(IStringC * iString, double reference, jvalue_ref values)
{
	return static_cast<std::string>(reinterpret_cast<IString*>(iString)->format(double, values)).c_str();
}
const char* IString_formatChoiceJSONStringRef(IStringC * iString, const char * reference, jvalue_ref* values)
{
	return static_cast<std::string>(reinterpret_cast<IString*>(iString)->format(std::string(reference), values)).c_str();
}*/

int IString_length(IStringC * iString)
{
	if ( !iString ) return -1;
	return reinterpret_cast<IString*>(iString)->length();
}
const char* IString_toString(IStringC * iString)
{
	if ( !iString ) return strdup("");
	return strdup( reinterpret_cast<IString*>(iString)->toString().c_str() );
}

const char* IString_formatChoiceLongStatic(const char * message, const long reference)
{
	return strdup( IString::formatChoice(std::string(message), reference).c_str() );
}
const char* IString_formatChoiceDoubleStatic(const char * message, const double reference)
{
	return strdup( IString::formatChoice(std::string(message), reference).c_str() );
}
const char* IString_formatWithValuesStatic(const char * message, StringMap* values)
{
	std::map<std::string,std::string> STDMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		STDMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));

	const char* result = strdup( IString::format(message, STDMap).c_str() );
	STDMap.clear();
	return result;
}
const char* IString_formatChoiceLongWithValuesStatic(const char * message, long reference, StringMap* values)
{
	std::map<std::string,std::string> STDMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		STDMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));

	const char* result = strdup( IString::formatChoice(message, reference, STDMap).c_str() );
	STDMap.clear();
	return result;
}
const char* IString_formatChoiceDoubleWithValuesStatic(const char * message, double reference, StringMap* values)
{
	std::map<std::string,std::string> STDMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		STDMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));

	const char* result = strdup( IString::formatChoice(message, reference, STDMap).c_str() );
	STDMap.clear();
	return result;
}

/*std::map<std::string, std::string> getCompatibleStringMap(StringMap* values)
{
	std::map<std::string,std::string> mainMap = std::map<std::string,std::string>();
	for (size_t i = 0; i < values->size; ++i)
		mainMap.insert(std::pair<std::string, std::string>(values->items[i].key, values->items[i].value));
	delete values;
	return mainMap;
}*/
