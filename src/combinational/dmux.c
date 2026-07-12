#include "combinational.h"

bits2_t dmux2_1(bit_t i, bit_t s)
{
    return (bits2_t)
    { 
        .bits = { 
            and_gate(not_gate(s), i), 
            and_gate(s, i) 
        } 
    };
}
bits4_t dmux4_1(bit_t i, bit_t s0, bit_t s1)
{
    bits2_t layer0 = dmux2_1(i, s1);
    bits2_t layer1_0 = dmux2_1(layer0.bits[0], s0);
    bits2_t layer1_1 = dmux2_1(layer0.bits[1], s0);
    return (bits4_t)
    {
        .bits = {
            layer1_0.bits[0],
            layer1_0.bits[1],
            layer1_1.bits[0],
            layer1_1.bits[1]
        }
    };
}

byte_t dmux8_1(bit_t i, bit_t s0, bit_t s1, bit_t s2)
{
    bits2_t layer0 = dmux2_1(i, s2);
    bits4_t layer1_0 = dmux4_1(layer0.bits[0], s0, s1);
    bits4_t layer1_1 = dmux4_1(layer0.bits[1], s0, s1);
    return (byte_t)
    {
        .bits = {
            layer1_0.bits[0],
            layer1_0.bits[1],
            layer1_0.bits[2],
            layer1_0.bits[3],
            layer1_1.bits[0],
            layer1_1.bits[1],
            layer1_1.bits[2],
            layer1_1.bits[3]
        }
    };
}
word_t dmux32_1(bit_t i, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4)
{
    bits4_t layer0 = dmux4_1(i, s3, s4);
    byte_t layer1_0 = dmux8_1(layer0.bits[0], s0, s1, s2);
    byte_t layer1_1 = dmux8_1(layer0.bits[1], s0, s1, s2);
    byte_t layer1_2 = dmux8_1(layer0.bits[2], s0, s1, s2);
    byte_t layer1_3 = dmux8_1(layer0.bits[3], s0, s1, s2);

    return (word_t) {
        .bits = {
            layer1_0.bits[0], layer1_0.bits[1], layer1_0.bits[2], layer1_0.bits[3],
            layer1_0.bits[4], layer1_0.bits[5], layer1_0.bits[6], layer1_0.bits[7],
            layer1_1.bits[0], layer1_1.bits[1], layer1_1.bits[2], layer1_1.bits[3],
            layer1_1.bits[4], layer1_1.bits[5], layer1_1.bits[6], layer1_1.bits[7],
            layer1_2.bits[0], layer1_2.bits[1], layer1_2.bits[2], layer1_2.bits[3],
            layer1_2.bits[4], layer1_2.bits[5], layer1_2.bits[6], layer1_2.bits[7],
            layer1_3.bits[0], layer1_3.bits[1], layer1_3.bits[2], layer1_3.bits[3],
            layer1_3.bits[4], layer1_3.bits[5], layer1_3.bits[6], layer1_3.bits[7]
        }
    };
}
