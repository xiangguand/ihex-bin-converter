#!/usr/bin/env bash

dut=./build/hex_bin_converter

set -e

(cd ./build/test && ctest .)


$dut -h


echo "===== Test from hex to bin ====="
rm -f test_8000000.bin
rm -f test_200000.bin
$dut -hex patterns/test.hex
diff test_200000.bin patterns/answer_200000.bin
if [ $? -ne 0 ]; then
    echo "===== Generating from hex to bin failed ====="
    exit 1
fi
diff test_8000000.bin patterns/answer_8000000.bin
if [ $? -ne 0 ]; then
    echo "===== Generating from hex to bin failed ====="
    exit 1
fi


echo "===== Test from bin to hex ====="
$dut -bin test_200000.bin 0x200000 test_8000000.bin 0x8000000 -m $(cat __main_address.txt) -o bin_to_hex_out.hex
diff patterns/test.hex bin_to_hex_out.hex
if [ $? -ne 0 ]; then
    echo "===== Generating from bin to hex failed ====="
    exit 1
fi

echo "===== Clean up ====="
rm -f test_8000000.bin
rm -f test_200000.bin
rm -f bin_to_hex_out.hex
rm -f __main_address.txt

echo "===== All test cases PASS ====="

