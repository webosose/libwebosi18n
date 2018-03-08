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
 * StringMap.h
 *
 * @author Oleksandr Gorbunov
 */

#ifndef STRINGMAP_H_
#define STRINGMAP_H_

#include <stdlib.h>

typedef struct PairItem {
	const char* key;
	const char* value;
} PairItem;
typedef struct StringMap {
	size_t size;
	size_t MAX_ITEMS;
	PairItem* items;
} StringMap;

StringMap* stringMap_create();
void stringMap_addItem(StringMap* map, PairItem* pairItem);
void stringMap_addKeyValue(StringMap* map, const char* key, const char* value);
void stringMap_addAll(StringMap* map, PairItem* values, const size_t size);

#endif /* STRINGMAP_H_ */
