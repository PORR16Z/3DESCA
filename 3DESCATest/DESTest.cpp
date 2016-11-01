#include <gtest/gtest.h>
#include "3DESCA/DES.hpp"

const TDESCA::chunk64 result(0x94d4436bc3b5b693);

TEST(DES, Basic)
{
    TDESCA::DES cipher;

    TDESCA::chunk64 in(0x6162636465666768); // abcdefgh
    TDESCA::chunk64 key(0x0102030405060708);
    TDESCA::chunk64 out = cipher.Process(key, in);

    ASSERT_EQ(result.val, out.val);
}
