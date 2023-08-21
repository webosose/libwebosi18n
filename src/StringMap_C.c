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
 * StringMap_C.c
 *
 *  Created on: Oct 16, 2013
 *      Author: oleksandr.gorbunov
 */

#include "webosi18n/c/StringMap_C.h"
#include <stdio.h>
#include <math.h>

#define INCREASING_STEP 10;

StringMap* stringMap_create()
{
	StringMap* mapPointer = malloc( sizeof(StringMap) );

	if (mapPointer != NULL) {
		mapPointer->size = 0;
		mapPointer->MAX_ITEMS = INCREASING_STEP;
		mapPointer->items = (PairItem*) malloc( mapPointer->MAX_ITEMS * sizeof(PairItem) );
	}
	return mapPointer;
}

void stringMap_addItem(StringMap* map, PairItem* pairItem)
{
	if (map == NULL) return;

	if (map->size < map->MAX_ITEMS) {
		map->items[map->size] = *pairItem;
	} else {
		map->MAX_ITEMS += INCREASING_STEP;
		map->items = (PairItem*) realloc(map->items, (map->MAX_ITEMS) * sizeof(PairItem));
		if (map->items == NULL) return;
		map->items[map->size] = *pairItem;
	}
	map->size++;
}

void stringMap_addKeyValue(StringMap* map, const char* key, const char* value)
{
	PairItem pairItem = {key, value};
	stringMap_addItem(map, &pairItem);
}

void stringMap_addAll(StringMap* map, PairItem* values, const size_t size)
{
	if (map == NULL) return;
	map->items = values;
	map->size = size;
	map->MAX_ITEMS = ceil(size);
}
