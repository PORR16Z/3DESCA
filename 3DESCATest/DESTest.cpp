#include <gtest/gtest.h>
#include "3DESCA/DES.hpp"

const TDESCA::chunk64 result(0x235ad2a8608edf37);

TEST(DES, Basic)
{
    TDESCA::DES cipher;

    TDESCA::chunk64 in(0x6162636465666768); // abcdefgh
    //TDESCA::chunk64 in(0x0123456789ABCDEF);
    //TDESCA::chunk64 key(0x133457799BBCDFF1);
    TDESCA::chunk64 key(0xF1DFBC9B79573413);
    TDESCA::chunk64 out = cipher.Process(key, in);

    EXPECT_EQ(result.val, out.val) << "In hex: " << std::endl << std::hex << std::setfill('0') <<
        out.val << " vs expected " << result.val << std::endl << std::endl;

    in.val = 0x6867666564636261; // abcdefgh
    key.val = 0x0102030405060708;
    out = cipher.Process(key, in);

    EXPECT_EQ(result.val, out.val) << "In hex: " << std::endl << std::hex << std::setfill('0') <<
        out.val << " vs expected " << result.val << std::endl << std::endl;

    in.val = 0x6162636465666768; // abcdefgh
    key.val = 0x0807060504030201;
    out = cipher.Process(key, in);

    EXPECT_EQ(result.val, out.val) << "In hex: " << std::endl << std::hex << std::setfill('0') <<
        out.val << " vs expected " << result.val << std::endl << std::endl;

    in.val = 0x6867666564636261; // abcdefgh
    key.val = 0x0807060504030201;
    out = cipher.Process(key, in);

    EXPECT_EQ(result.val, out.val) << "In hex: " << std::endl << std::hex << std::setfill('0') <<
        out.val << " vs expected " << result.val << std::endl << std::endl;
}
