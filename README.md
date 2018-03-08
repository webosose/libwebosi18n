libwebosi18n
============

Summary
-------
webOS Native Internationalization library (for C and C++ applications)

Description
-----------
Library allows to localize your native applications (C or C++ written).
It uses ResBundle instance to load appropriate string for current locale.

How to Build on Linux
---------------------

## Dependencies

Below are the tools and libraries (and their minimum versions) required to build libwebosi18n:

- cmake (version required by cmake-modules-webos)
- gcc 4.6.3
- g++ 4.6.3
- libpbnjson 2.1.1
- make (any version)
- cmake-modules-webos 1.0.0 RC3
- pkg-config 0.26

## Enabling Unit Test

If you want to build and run the Unit Test suite for libwebosi18n, you need to
have the following library installed.

* GTest

## Building

Once you have downloaded the source, enter the following to build it (after
changing into the directory under which it was downloaded):

    $ mkdir BUILD
    $ cd BUILD
    $ cmake ..
    $ make


Copyright and License Information
---------------------------------
Copyright (c) 2013-2018 LG Electronics, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

SPDX-License-Identifier: Apache-2.0
