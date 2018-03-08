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

#include "webosi18n/cxx/ResBundle.h"
#include <string.h>
#define BUFFER_SIZE 256;

extern "C" {
  #include "webosi18n/c/ResBundle_C.h"
}

ResBundleC * resBundle_create(const char * locale, const char * file_path)
{
    return reinterpret_cast<ResBundleC*>( new ResBundle(locale, file_path) );
}
ResBundleC * resBundle_createWithRootPath(const char* locale, const char* file_name, const char* root_path)
{
	return reinterpret_cast<ResBundleC*>( new ResBundle(locale, file_name, root_path) );
}
void resBundle_destroy(ResBundleC * bundle)
{
	if ( !bundle ) return;
	delete reinterpret_cast<ResBundle*>(bundle);
}

bool resBundle_containsSource(ResBundleC * bundle, const char * source)
{
	if ( !bundle ) return false;
	return reinterpret_cast<ResBundle*>(bundle)->containsSource(source);
}

const char* resBundle_getLocString(ResBundleC * bundle, const char * source)
{
	if ( !bundle ) return strdup("");
	return strdup( reinterpret_cast<ResBundle*>(bundle)->getLocString(source).c_str() );
}
const char* resBundle_getLocStringWithKey(ResBundleC * bundle, const char * key, const char * source)
{
	if ( !bundle ) return strdup("");
	return strdup( reinterpret_cast<ResBundle*>(bundle)->getLocString(key, source).c_str() );
}
const char* resBundle_getLocale(ResBundleC * bundle)
{
	if ( !bundle ) return strdup("");
	return strdup( reinterpret_cast<ResBundle*>(bundle)->getLocale().c_str() );
}
