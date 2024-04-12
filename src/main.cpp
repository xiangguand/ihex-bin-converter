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
 * \brief    HEX to BIN converter or BIN to HEX converter.
 * \version  v1.0.1
 * \date     12. April. 2024
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

	if (1 == argc) {
		cout << "Please specify the filename." << endl;
		return -1;
	}

	string hex_out_tag = "test";
	string hex_filename = "";
	string bin_to_hex_filename = "bin.hex";
	vector<string> bin_filenames;
	vector<string> bin_offsets;
	uint32_t __main_address = 0xFFFFFFFF;

	int mode = 0;
	// 1 -> hex to bin
	// 2 -> bin to hex

	int i = 1;
	while (i < argc) {
		// cout << i << "," << argv[i] << endl;
		if (argv[i] == string("-h")) {
			cout << "Usage:  -h | Print help message" << endl;
			cout << "        -hex {filename} | Filename of input hex provided and tag is \"test\" "
			     << endl;
			cout << "        -hex {filename} {output file tag} | Filename of input hex and tag is provided"
			     << endl;
			cout << "        -bin {bin filename} {offset(hex)} | Filename of input bin and offset is base of bin. It can pass multible bin file"
			     << endl;
			cout << "        -o   {filename} | Filename of output all bin and offset provided."
			     << endl;
			cout << "        -m   {adress}   | Keil __main function address."
			     << endl;
			return 0;
		} else if (0 == mode && argv[i] == string("-hex")) {
			if (i + 1 < argc) {
				cout << "Filename is " << argv[i + 1] << endl;
				hex_filename = string(argv[i + 1]);
			}
			mode = 1;
			break;
		} else if (0 == mode && argv[i] == string("-bin")) {
			i++;
			mode = 2;
		} else if (argv[i] == string("-o")) {
			// cout << "Output " << endl;
			if (i + 1 < argc) {
				cout << "Filename is " << argv[i + 1] << endl;
				bin_to_hex_filename = string(argv[i + 1]);
			}
			i += 2;
		} else if (argv[i] == string("-m")) {
			// cout << "Output " << endl;
			if (i + 1 < argc) {
				__main_address = strtoul(argv[i + 1], NULL, 16);
			}
			i += 2;
		} else if (2 == mode) {
			if (i + 2 > argc) {
				cout << "Invalid command." << endl;
				return -1;
			}
			bin_filenames.push_back(string(argv[i]));
			bin_offsets.push_back(string(argv[i + 1]));
			i += 2;
		} else {
			return -2;
		}
	}

	if (0 == mode) {
		cout << "Invalid command." << endl;
	} else if (1 == mode) {
		/* Start handling HEX to BIN conversion. */
		cout << "Convert HEX to BIN" << endl;
		IHex hex_obj = IHex(hex_filename);
		if (hex_obj.is_valid()) {
			cout << "File is valid." << endl;
			hex_obj.write_bin("test");
		} else {
			cout << "File is invalid." << endl;
		}
	} else {
		/* Start handling BIN to HEX conversion. */
		cout << "Convert BIN to HEX" << endl;
		for (int i = 0; i < (int)bin_filenames.size(); i++) {
			cout << "File is " << bin_filenames[i]
			     << " with offset " << bin_offsets[i] << endl;
		}
		cout << "Output file is " << bin_to_hex_filename << endl;
		if(0xFFFFFFFF == __main_address) {
			IHex hex_obj = IHex(bin_filenames, bin_offsets, bin_to_hex_filename);
		}
		else {
			IHex hex_obj = IHex(bin_filenames, bin_offsets, bin_to_hex_filename, __main_address);
		}
	}

	return 0;
}
