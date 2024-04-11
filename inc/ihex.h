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

#ifndef IHEX_H_
#define IHEX_H_

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
	vector<string> read_hex_file(string filename);
	void parse_hex_string(vector<string> hex_string);
	void parse_hex_line(string line);
	uint8_t calculate_checksum(string line);
	uint8_t get_byte_count(string line);
	uint16_t get_address(string line);
	uint8_t get_record_type(string line);
	void get_data(string line, vector<uint8_t> &data);
	bool check_checksum(string line);
	void feed_bin(vector<uint8_t> bin);
	bool is_valid();
	void write_bin(string filename);
	void write_hex(string filename);

    private:
	bool parse_flag = false;
	vector<binData> bin_files;
    binData bin_data;
};

} /* namespace ihex */

#endif /* IHEX_H_ */
