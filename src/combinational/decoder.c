#include "combinational.h"

bits2_t decoder2(bit_t s)
{
    return dmux2_1(1, s);
}

bits4_t decoder4(bit_t s0, bit_t s1)
{
    return dmux4_1(1, s0, s1);
}

byte_t decoder8(bit_t s0, bit_t s1, bit_t s2)
{
    return dmux8_1(1, s0, s1, s2);
}

word_t decoder32(bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4)
{
    return dmux32_1(1, s0, s1, s2, s3, s4);
}
