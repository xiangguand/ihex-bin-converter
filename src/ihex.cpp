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
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace ihex;

static void write___main_address(uint32_t __main_address)
{
	ofstream file;
	file.open("__main_address.txt");
	if (file.is_open() == false) {
		cout << "File cannot open!" << endl;
		return;
	}
	file << hex << "0x" << __main_address;
	file.close();
}

IHex::IHex()
{
	parse_flag = false;
	valid_flag = true;
}

IHex::IHex(string filename)
{
	parse_flag = false;
	valid_flag = true;
	/* Read file and parse it */
	vector<string> lines;
	lines = read_hex_file(filename);
	if (0 == lines.size()) {
		return;
	}
	parse_hex_string(lines);
}

IHex::IHex(vector<string> bin_filenames, vector<string> bin_offsets,
	   string hex_filename, uint32_t __main_address)
{
	write_hex(bin_filenames, bin_offsets, hex_filename, __main_address);
}

void IHex::write_hex(vector<string> bin_filenames, vector<string> bin_offsets,
		     string hex_filename, uint32_t __main_address)
{
	// EXTENDED LINEAR ADDRESS 0
	// DATA...
	// EXTENDED LINEAR ADDRESS 1
	// DATA...
	// START LINEAR ADDRESS
	// END OF FILE

	unsigned long n = bin_filenames.size();
	if (n != bin_offsets.size()) {
		cout << "Number of bin files and offsets are not equal!"
		     << endl;
		valid_flag = false;
		return;
	}

	file = ofstream(hex_filename);
	if (file.is_open() == false) {
		cout << "File cannot open!" << endl;
		valid_flag = false;
		return;
	}

	for (unsigned long i = 0; i < n; i++) {
		write_extended_linear_address(stoi(bin_offsets[i], nullptr, 16),
					      file);
		write_data(read_bin_file(bin_filenames[i]), file);
	}

	if (__main_address != 0xFFFFFFFF) {
		write_start_linear_address(__main_address, file);
	}

	write_endfile(file);
	file.close();
}

void IHex::write_extended_linear_address(uint32_t address, ofstream &wf)
{
	stringstream ss;
	ss << ":02000004" << hex << setw(4) << setfill('0') << (address >> 16);

	string temp = ss.str() + "00";
	uint32_t chksum = calculate_checksum(temp);

	ss << hex << setw(2) << setfill('0') << chksum << '\r' << endl;

	string hexString = ss.str();
	transform(hexString.begin(), hexString.end(), hexString.begin(),
		  [](unsigned char c) { return std::toupper(c); });

	wf << hexString;
}

void IHex::write_start_linear_address(uint32_t address, ofstream &wf)
{
	stringstream ss;
	ss << ":04000005" << hex << setw(8) << setfill('0') << address;

	string temp = ss.str() + "00";
	uint32_t chksum = calculate_checksum(temp);

	ss << hex << setw(2) << setfill('0') << chksum << '\r' << endl;

	string hexString = ss.str();
	transform(hexString.begin(), hexString.end(), hexString.begin(),
		  [](unsigned char c) { return std::toupper(c); });

	wf << hexString;
}

void IHex::write_data(vector<uint8_t> data, ofstream &wf)
{
	stringstream ss;

	unsigned long n = data.size();
	unsigned long ws = 0;

	while ((ws + 1) * 16 < n) {
		stringstream ss;
		ss << hex << ":10" << setw(4) << setfill('0') << ws * 16
		   << "00";
		for (unsigned long i = ws * 16; i < (ws + 1) * 16; i++) {
			ss << setw(2) << setfill('0') << hex << (int)data[i];
		}

		string temp = ss.str() + "00";
		uint32_t chksum = calculate_checksum(temp);

		ss << hex << setw(2) << setfill('0') << chksum << '\r' << endl;
		string hexString = ss.str();
		transform(hexString.begin(), hexString.end(), hexString.begin(),
			  [](unsigned char c) { return std::toupper(c); });

		wf << hexString;

		ws++;
	}
	if (ws * 16 < n) {
		unsigned int residual_bytes = n - ws * 16;
		stringstream ss;
		ss << hex << ":" << setw(2) << setfill('0') << residual_bytes
		   << setw(4) << setfill('0') << ws * 16 << "00";
		for (unsigned int i = ws * 16; i < n; i++) {
			ss << setw(2) << setfill('0') << hex << (int)data[i];
		}
		string temp = ss.str() + "00";
		uint32_t chksum = calculate_checksum(temp);
		ss << hex << setw(2) << setfill('0') << chksum << '\r' << endl;
		string hexString = ss.str();
		transform(hexString.begin(), hexString.end(), hexString.begin(),
			  [](unsigned char c) { return std::toupper(c); });

		wf << hexString;
	}
}

void IHex::write_endfile(ofstream &wf)
{
	stringstream ss;
	ss << ":00000001FF" << '\r' << endl;
	string hexString = ss.str();
	transform(hexString.begin(), hexString.end(), hexString.begin(),
		  [](unsigned char c) { return std::toupper(c); });

	wf << hexString;
}

vector<string> IHex::read_hex_file(string filename)
{
	vector<string> lines;
	ifstream file(filename);

	if (file.is_open() == false) {
		cout << "File not found!" << endl;
		valid_flag = false;
		return lines;
	}

	string line = "";
	char ch;
	while (file.read(&ch, 1)) {
		if (ch == '\r' || ch == '\n') {
			if (line.size() > 0) {
				lines.push_back(line);
				line = "";
			}
		} else {
			line += ch;
		}
	}
	file.close();
	parse_flag = true;

	return lines;
}

vector<uint8_t> IHex::read_bin_file(string filename)
{
	vector<uint8_t> data;
	ifstream file(filename, ios::binary);

	if (file.is_open() == false) {
		cout << "File not found!" << endl;
		valid_flag = false;
		return data;
	}

	char ch;
	while (file.read(&ch, 1)) {
		data.push_back(ch);
	}
	file.close();

	return data;
}

void IHex::parse_hex_string(vector<string> lines)
{
	for (auto line : lines) {
		parse_hex_line(line);
	}
}

void IHex::parse_hex_line(string line)
{
	vector<uint8_t> addr;
	if (false == check_checksum(line)) {
		cout << "CHECKSUM ERROR " << line << endl;
		cout << "Pass this line" << endl;
		valid_flag = false;
	} else if (':' == line[0]) {
		switch (get_record_type(line)) {
		case IHex::RecordType::DATA:
			/* code */
			cout << "DATA " << line << endl;
			get_data(line, bin_data.bin);
			break;
		default:
		case IHex::RecordType::END_OF_FILE:
			/* code */
			cout << "END OF FILE " << line << endl;
			if (bin_data.bin.size() > 0) {
				bin_files.push_back(bin_data);
			}
			break;
		case IHex::RecordType::EXTENDED_SEGMENT_ADDRESS:
			/* code */
			cout << "EXTENDED SEGMENT ADDRESS " << line << endl;
			break;
		case IHex::RecordType::START_SEGMENT_ADDRESS:
			/* code */
			cout << "START SEGMENT ADDRESS " << line << endl;
			break;
		case IHex::RecordType::EXTENDED_LINEAR_ADDRESS:
			/* code */
			cout << "EXTENDED LINEAR ADDRESS " << line << endl;
			if (bin_data.bin.size() > 0) {
				bin_files.push_back(bin_data);
			}
			bin_data.bin.clear();
			bin_data.start_addr = 0;

			get_data(line, addr);
			for (int i = 0; i < (int)addr.size(); i++) {
				bin_data.start_addr <<= 8;
				bin_data.start_addr |= addr[i];
			}
			bin_data.start_addr <<= 16;
			cout << "Start address: " << hex << bin_data.start_addr
			     << dec << endl;
			break;
		case IHex::RecordType::START_LINEAR_ADDRESS:
			/* code */
			cout << "START LINEAR ADDRESS " << line << endl;
			__main_address_ = stoul(line.substr(9, 8), nullptr, 16);
			write___main_address(__main_address_);
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
	for (int i = 1; i < (int)line.size() - 2; i += 2) {
		checksum += stoi(line.substr(i, 2), nullptr, 16);
	}

	return (~checksum) + 1;
}

uint8_t IHex::get_byte_count(string line)
{
	return stoi(line.substr(1, 2), nullptr, 16);
}

uint16_t IHex::get_address(string line)
{
	return stoi(line.substr(3, 4), nullptr, 16);
}

uint8_t IHex::get_record_type(string line)
{
	return stoi(line.substr(7, 2), nullptr, 16);
}

void IHex::get_data(string line, vector<uint8_t> &data)
{
	for (int i = 9; i < (int)line.size() - 2; i += 2) {
		data.push_back(stoi(line.substr(i, 2), nullptr, 16));
	}
}

bool IHex::check_checksum(string line)
{
	uint8_t checksum = calculate_checksum(line);
	if (checksum == stoi(line.substr(line.size() - 2, 2), nullptr, 16)) {
		return true;
	}

	return false;
}

bool IHex::is_valid()
{
	return valid_flag;
}

void IHex::write_bin(string filename)
{
	for (auto wbin : bin_files) {
		std::stringstream stream;
		stream << std::hex << wbin.start_addr;
		string bin_filename = filename + "_" + stream.str() + ".bin";

		cout << "Write " << bin_filename << endl;
		ofstream bin_file(bin_filename, ios::binary);
		bin_file.write((char *)wbin.bin.data(), wbin.bin.size());
		bin_file.close();
	}
}
