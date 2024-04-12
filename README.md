[![Tests](https://github.com/xiangguand/ihex-bin-converter/actions/workflows/test.yaml/badge.svg)](https://github.com/xiangguand/ihex-bin-converter/actions/workflows/test.yaml)

<!-- ABOUT THE PROJECT -->
## About The Project
This project is to convert ihex file to bin file or convert bin file to hex file.

Example hex file contains binary data with specific address.
* test.hex:
    * 0x08000000
    * 0x00200000


### Built With
* Using toolchain:
    * cmake
    * clang or gcc

**How to build ?**
```bash
./build.sh
```
After building the project, the executable file will locate at "./build/hex_bin_converter".

<!-- GETTING STARTED -->
## Getting Started
**How to convert from hex to bin file(s) ?**
```bash
./build/hex_bin_converter -hex patterns/test.hex
```
After converting hex to bin file, it will generate files {tag}_{base address of binary contens}.bin and address of `__main` written in __main_address.txt.
  
  
**How to convert from bin file(s) to hex file ?**
```bash
./build/hex_bin_converter -bin test_200000.bin 0x200000 test_8000000.bin 0x8000000 -m 0x80001f9 -o bin_to_hex_out.hex
```
Intel HEX format can integrate multiple of binary files, therefore, we have to provide base address to conterter.  
`-m` option is only for MDK Keil to tell it where the `__main` function is.
  

### Installation
You can simply copy the program to /usr/bin. After copying the program to user program directory on Linux, now you can use this command.
```bash
sudo cp ./build/hex_bin_converter /usr/bin/
```


<!-- USAGE EXAMPLES -->
## Usage
See **Getting Started** section.

<!-- CONTACT -->
## Contact
xiangguand@gmail.com

