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

// -hex {hex filename}
// -hex {hex filename} {output file tag}
// -bin {bin filename00} {offset(hex)}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	cout << "Hello World!" << endl;

	if (1 == argc) {
		cout << "Please specify the filename." << endl;
		return -1;
	}

	string hex_out_tag = "test";
	string hex_filename = "";
	string bin_to_hex_filename = "bin.hex";
	vector<string> bin_filenames;
	vector<string> bin_offsets;

	int mode = 0;
	// 1 -> hex to bin
	// 2 -> bin to hex

	int i = 1;
	while (i < argc) {
		cout << argv[i] << endl;
		if (argv[i] == string("-h")) {
			cout << "Usage:  -h | Print help message" << endl;
			cout << "        -hex {filename} | Filename of input hex provided and tag is \"test\" "
			     << endl;
			cout << "        -hex {filename} {output file tag} | Filename of input hex and tag is provided"
			     << endl;
			cout << "        -bin {bin filename} {offset(hex)} | Filename of input bin and offset is base of bin. It can pass multible bin file"
			     << endl;
			cout << "        -o {filename} | Filename of output all bin and offset provided."
			     << endl;
			return 0;
		} else if (argv[i] == string("-hex")) {
			if (i + 1 < argc) {
				cout << "Filename is " << argv[i + 1] << endl;
				hex_filename = string(argv[i + 1]);
			}
			mode = 1;
			break;
		} else if (argv[i] == string("-bin")) {
			if (i + 2 >= argc) {
				cout << "Invalid command." << endl;
				return -1;
			} else {
				while (i + 2 < argc) {
					cout << "Filename is " << argv[i + 1]
					     << endl;
					cout << "Offset is " << argv[i + 2]
					     << endl;
					bin_filenames.push_back(
						string(argv[i + 1]));
					bin_offsets.push_back(
						string(argv[i + 2]));
					i += 2;
				}
			}
			i++;
			mode = 2;
		} else if (argv[i] == string("-o")) {
			if (i + 1 < argc) {
				cout << "Filename is " << argv[i + 1] << endl;
				bin_to_hex_filename = string(argv[i + 1]);
			}
			i += 2;
		} else {
			return -2;
		}
	}

	
	if(0 == mode) {
		cout << "Invalid command." << endl;
	}
	else if(1 == mode) {
		IHex hex_obj = IHex(hex_filename);
		if (hex_obj.is_valid()) {
			cout << "File is valid." << endl;
			hex_obj.write_bin("test");
		} else {
			cout << "File is invalid." << endl;
		}
	}
	else {
		// bin
		IHex hex_obj = IHex(bin_filenames, bin_offsets);
	}

	return 0;
}
