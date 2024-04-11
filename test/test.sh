#!/usr/bin/env bash

dut=./build/main

set -e

(cd ./build/test && ctest .)

echo "===== All test cases PASS ====="

