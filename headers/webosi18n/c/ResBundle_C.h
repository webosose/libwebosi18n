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

#ifndef RESBUNDLEC_H_
#define RESBUNDLEC_H_

#include <stdbool.h>
/**
 * C Wrapper for ResBundle class
 *
 * @see for more information go to ResBundle.h
 */
struct ResBundleC;
typedef struct ResBundleC ResBundleC;

ResBundleC * resBundle_create(const char * locale, const char * file_path);
ResBundleC * resBundle_createWithRootPath(const char * locale, const char * file_name, const char * root_path);
void resBundle_destroy(ResBundleC * bundle);

bool resBundle_containsSource(ResBundleC * bundle, const char * source);
const char* resBundle_getLocString(ResBundleC * bundle, const char * source);
const char* resBundle_getLocStringWithKey(ResBundleC * bundle, const char * key, const char * source);
const char* resBundle_getLocale(ResBundleC * bundle);

#endif /* RESBUNDLEC_H_ */
