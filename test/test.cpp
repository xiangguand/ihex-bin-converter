#include "gtest/gtest.h"
#include "ihex.h"

using namespace std;
using namespace ihex;

TEST (Example, ItShouldAlwaysPass) { 
    EXPECT_EQ(18.0, 18.0);
}

TEST (IntelHexFormat, testIHexGetAddress) { 
    IHex obj;
    uint16_t addr = obj.get_address(":0B0010006164647265737320676170A7");
    EXPECT_EQ(0x0010, addr);
}

TEST (IntelHexFormat, testIHexCheckChecksum) { 
    IHex obj;
    bool check;
    check = obj.check_checksum(":0B0010006164647265737320676170A7");
    EXPECT_EQ(true, check);
    check = obj.check_checksum(":0B0010006164647265737320676171A7");
    EXPECT_EQ(false, check);
    check = obj.check_checksum(":0B1010006164647265737320676170A7");
    EXPECT_EQ(false, check);
}

