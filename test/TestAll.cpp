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

#include "TestResBundle.h"
#include "TestResBundle_C.h"
#include "TestIString.h"
#include "TestIString_C.h"
#include "TestWebOSLocale.h"
#include "TestWebOSLocale_C.h"
using namespace std;
#include <iostream>
#include <iomanip>
#include <boost/exception/all.hpp>
#include <pbnjson.hpp>

int main()
{
	cout << "----------<<< libwebosi18n project testing started >>>----------" << endl;
	cout << "-------------------------------------------------------------\n" << endl;
	clock_t begin = clock();

	cout << setprecision(6) << fixed;

	int testsNumber = 0;
	int failuresNumber = 0;
	int* tests = &testsNumber;
	int* failures = &failuresNumber;

	try {
	runTestResBundle(tests, failures);
	runTestResBundle_C(tests, failures);

	try {
		runTestIString(tests, failures);
		runTestIString_C(tests, failures);
	} catch(pbnjson::JValue::InvalidType const& ex) {
		cout << "\npbnjson::JValue::InvalidType exception was thrown in runTestIStirng test\n" << endl;
	}

	runTestWebOSLocale(tests, failures);
	runTestWebOSLocale_C(tests, failures);

	} catch(boost::exception const& ex) {
		cout << "\nBoost exception was thrown in runTestIStirng_C test\n" << endl;
	}

	const double timeElapsed = ((double)(clock() - begin))/CLOCKS_PER_SEC;
	const double testsCoverage = (((double)(testsNumber - failuresNumber)) / testsNumber) * 100;
	cout << "\nTests total elapsed time: "<< timeElapsed << " seconds\n" << endl;
	cout << "Passed tests total number: "<< testsNumber << ", total failures: " << failuresNumber <<
			", percentage of passed tests: " << testsCoverage << "%" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "----------<<< libwebosi18n project testing finished >>>---------" << endl;
	return 0;
}
