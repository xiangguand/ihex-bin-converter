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
 * \version  v1.0.1
 * \date     12. April. 2024
 *
 * \author   Xiang-Guan Deng
 *
 * -----------------------------------------------------------------------------
 **/

#ifndef IHEX_H_
#define IHEX_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace ihex
{
using namespace std;

class binData {
    public:
	binData()
	{
	}
	uint64_t start_addr = 0;
	vector<uint8_t> bin;
};

class IHex {
    public:
	/* Declare iHex record type */
	enum RecordType {
		DATA = 0x00,
		END_OF_FILE = 0x01,
		EXTENDED_SEGMENT_ADDRESS = 0x02,
		START_SEGMENT_ADDRESS = 0x03,
		EXTENDED_LINEAR_ADDRESS = 0x04,
		START_LINEAR_ADDRESS = 0x05
	};

	IHex();
	IHex(string filename);
	IHex(vector<string> bin_filenames, vector<string> bin_offsets,
	     string hex_filename, uint32_t __main_addresss=0xFFFFFFFF);
	void write_hex(vector<string> bin_filenames,
			     vector<string> bin_offsets, string hex_filename,
			     uint32_t __main_address);
	void write_extended_linear_address(uint32_t address, ofstream &wf);
	void write_start_linear_address(uint32_t address, ofstream &wf);
	void write_data(vector<uint8_t> data, ofstream &wf);
	void write_endfile(ofstream &wf);
	vector<string> read_hex_file(string filename);
	vector<uint8_t> read_bin_file(string filename);
	void parse_hex_string(vector<string> hex_string);
	void parse_hex_line(string line);
	uint8_t calculate_checksum(string line);
	uint8_t get_byte_count(string line);
	uint16_t get_address(string line);
	uint8_t get_record_type(string line);
	void get_data(string line, vector<uint8_t> &data);
	bool check_checksum(string line);
	bool is_valid();
	void write_bin(string filename);

    private:
	bool parse_flag = false;
	bool valid_flag = true;
	vector<binData> bin_files;
	binData bin_data;
	ofstream file;
	uint32_t __main_address_ = 0xFFFFFFFF;
};

} /* namespace ihex */

#endif /* IHEX_H_ */
