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