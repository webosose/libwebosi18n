# Copyright (c) 2013-2018 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 2.8.7)
project(webosi18n CXX)

enable_language(C CXX)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC4)
webos_component(1 0 1)

include(FindPkgConfig)

pkg_check_modules(PBNJSON_CPP REQUIRED pbnjson_cpp)
include_directories(${PBNJSON_CPP_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${PBNJSON_CPP_CFLAGS_OTHER})

pkg_check_modules(PBNJSON_C REQUIRED pbnjson_c)
include_directories(${PBNJSON_C_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${PBNJSON_C_CFLAGS_OTHER})

find_package(Boost REQUIRED COMPONENTS regex)
include_directories(${Boost_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${Boost_CFLAGS_OTHER})

if (LOCAL_UNITTEST)
set(LD_LIBRARY_PATH /usr/local/webos/usr/lib/libpbnjson_cpp.so)
endif()
set(REQUIRED_LIBS
	${PBNJSON_C_LDFLAGS}
	${PBNJSON_CPP_LDFLAGS}
	${Boost_LIBRARIES}
	${LD_LIBRARY_PATH}
	)

set(HEADERS headers/)
set(CXX_HEADERS ${HEADERS}webosi18n/cxx/)
set(C_HEADERS ${HEADERS}webosi18n/c/)
set(SOURCES_DIR src/)

include_directories(${HEADERS})
include_directories(${CXX_HEADERS})
include_directories(${C_HEADERS})
include_directories(${SOURCES_DIR})

set(SOURCE_FILES_SET
	${SOURCES_DIR}LocaleMatcher.cpp
	${SOURCES_DIR}WebOSLocale.cpp
	${SOURCES_DIR}WebOSLocale_C.cpp
	${SOURCES_DIR}ResBundle.cpp
	${SOURCES_DIR}ResBundle_C.cpp
	${SOURCES_DIR}StringMap_C.c
	${SOURCES_DIR}IString.cpp
	${SOURCES_DIR}IString_C.cpp
	)

set(SOURCE ${SOURCE_FILES_SET})
add_library(webosi18n SHARED ${SOURCE})
target_link_libraries(webosi18n ${REQUIRED_LIBS})
webos_build_library(TARGET webosi18n HEADERS ${HEADERS})

webos_build_pkgconfig(files/pkgconfig/webosi18n)

set(TEST_DIR test/)
set(RES_DIR res/)
include_directories(${TEST_DIR})

set(TEST_STUFF
	${TEST_DIR}TestResBundle.cpp
	${TEST_DIR}TestResBundle_C.c
	${TEST_DIR}TestIString.cpp
	${TEST_DIR}TestIString_C.c
	${TEST_DIR}TestWebOSLocale.cpp
	${TEST_DIR}TestWebOSLocale_C.c
	${TEST_DIR}TestAll.cpp
	)
add_subdirectory(${RES_DIR})
set(TEST ${SOURCE} ${TEST_STUFF})
add_executable(TestAllStuff ${TEST})
target_link_libraries(TestAllStuff ${REQUIRED_LIBS})
