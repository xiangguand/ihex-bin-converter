/**
 * Copyright (C) 2024 Xiang-Guan Deng Limited. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -----------------------------------------------------------------------------
 *
 * \file     main.cpp
 * \brief    Example main function. In this function, it will call C function and try to execute it.
 * \version  v1.0.0
 * \date     08. April. 2023
 *
 * \author   Xiang-Guan Deng
 *
 * -----------------------------------------------------------------------------
 **/

#include <iostream>

#include <ihex.h>

using namespace std;
using namespace ihex;

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	cout << "Hello World!" << endl;

	if(1 == argc) {
		cout << "Please specify the filename." << endl;
		return -1;
	}

	string filename = argv[1];
	IHex hex_obj = IHex(filename);
	if(hex_obj.is_valid()) {
		cout << "File is valid." << endl;
	}
	else {
		cout << "File is invalid." << endl;
	}

	return 0;
}
