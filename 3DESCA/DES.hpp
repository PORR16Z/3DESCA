#pragma once
#include <cstdint>
#include <array>

class DES
{
    union chunk64
    {
        std::array<uint8_t, 8> arr;
        uint64_t val;

        // arr is inverted val:
        // val = 0x0102030405060708 will result in
        // arr = {8, 7, 6, 5, 4, 3, 2, 1};
    };

    union chunk48
    {
        std::array<uint8_t, 6> arr;
        uint64_t val;
    };

    union chunk32
    {
        std::array<uint8_t, 4> arr;
        uint32_t val;
    };

    chunk64 InitPerm(chunk64 msg);
    chunk64 FinalPerm(chunk64 ciph);
    chunk48 Expansion(chunk32 data);
    uint8_t Substitution(uint8_t sBoxNo, uint8_t inputVal);
    chunk32 SBoxPermutation(chunk32 data);
    chunk64 PermutedChoice1(chunk64 key);
    chunk48 PermutedChoice2(chunk64 key);
    chunk32 Feistel(chunk32 data, chunk48 subKey);
    uint32_t RotateHalfkeyLeft(chunk32 halfKey, uint8_t n);

public:
    DES() {};
    ~DES() {};
    //bool Init(uint64_t key, std::vector<uint8_t> message);
    chunk64 Process(chunk64 key, chunk64 data);
        // split text into DES::chunk64 chunks
        // get 64bit key
        // remove 8bits from key for parity check - the key is now 56bit
        // get single chunk of data
        // put it into Initial Permutation
        // split into 32bit parts: L1 and R1
        // R1 goes into Feistel, becomes Rf1
        //// 32bit chunk AND single 48bit subkey (different for each of 16 rounds) comes into Feistel
        //// 32bit chunk is expanded to 48bits, referred to as X1
        //// X2 = X1 xor subkey
        //// X2 is split into 8 6bit parts
        //// each part is put into subsitution func with ascending S-box number (from 0 - 7)
        //// output of each part is put together into 32bit X3
        //// X3 goes into SBoxPermutation func and result comes out (here for R1, result is Rf1)
        // L2 = R1, R2 = L1 xor Rf1
        // repeat another 15 times
        // join L = L16 xor Rf16 and R = R16
        // put into Final Permutation
        // u got single chunk of ciphertext
    //std::vector<uint8_t> Finish();
};