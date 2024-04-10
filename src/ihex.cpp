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
 * \file     ihex.h
 * \brief    Index hex format converter.
 * \version  v1.0.0
 * \date     10. April. 2023
 *
 * \author   Xiang-Guan Deng
 *
 * -----------------------------------------------------------------------------
 **/

#include "ihex.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace ihex;

IHex::IHex()
{
	parse_flag = false;
}

IHex::IHex(string filename)
{
	/* Read file and parse it */
	vector<string> lines;
	lines = read_hex_file(filename);
	if (0 == lines.size()) {
		return;
	}
	parse_hex_string(lines);
}

vector<string> IHex::read_hex_file(string filename)
{
	vector<string> lines;
	ifstream file(filename);

	if (file.is_open() == false) {
		cout << "File not found!" << endl;
		return lines;
	}

	string line = "";
    char ch;
    while(file.read(&ch, 1)) {
        if(ch =='\r' || ch == '\n') {
            if(line.size() > 0) {
                lines.push_back(line);
                line = "";
            }
        }
        else {
            line += ch;
        }
    }
	file.close();

	return lines;
}

void IHex::parse_hex_string(vector<string> lines)
{
	for (auto line : lines) {
		parse_hex_line(line);
	}
}

void IHex::parse_hex_line(string line)
{
    if(false == check_checksum(line)) {
        cout << "CHECKSUM ERROR " << line << endl;
        cout << "Pass this line" << endl;
    }
	else if (':' == line[0]) {
		switch (stoi(line.substr(1, 2))) {
		case IHex::RecordType::DATA:
			/* code */
            
			break;
		default:
		case IHex::RecordType::END_OF_FILE:
			/* code */
			break;
		case IHex::RecordType::EXTENDED_SEGMENT_ADDRESS:
			/* code */
			break;
		case IHex::RecordType::START_SEGMENT_ADDRESS:
			/* code */
			break;
		case IHex::RecordType::EXTENDED_LINEAR_ADDRESS:
			/* code */
			break;
		case IHex::RecordType::START_LINEAR_ADDRESS:
			/* code */
			break;
		}
	} else {
		// pass, make it increase fault tolerance
		cout << "PASS " << line;
	}
}

uint8_t IHex::calculate_checksum(string line)
{
	uint8_t checksum = 0;
	for (int i = 1; i < line.size() - 2; i += 2) {
		checksum += stoi(line.substr(i, 2), nullptr, 16);
	}

	return (~checksum) + 1;
}

bool IHex::check_checksum(string line)
{
	uint8_t checksum = calculate_checksum(line);
	if (checksum == stoi(line.substr(line.size() - 2, 2), nullptr, 16)) {
		return true;
	}
	return false;
}

void IHex::feed_bin(vector<uint8_t> bin)
{
}

bool IHex::is_valid()
{
	return true;
}

void IHex::write_bin()
{
}

void IHex::write_hex(string filename)
{
}