#include "combinational.h"

bits2_t decoder2(bit_t s)
{
    bits2_t result = { .bits = {not_gate(s), s} };
    return result;
}

bits4_t decoder4(bit_t s0, bit_t s1)
{
    bits4_t result = { 
        .bits = {
            not_gate(s1) && not_gate(s0),
            not_gate(s1) && s0,
            s1 && not_gate(s0),
            s1 && s0
        }
    };
    return result;
}

byte_t decoder8(bit_t s0, bit_t s1, bit_t s2)
{
    byte_t result = { 
        .bits = {
            not_gate(s2) && not_gate(s1) && not_gate(s0),
            not_gate(s2) && not_gate(s1) && s0,
            not_gate(s2) && s1 && not_gate(s0),
            not_gate(s2) && s1 && s0,
            s2 && not_gate(s1) && not_gate(s0),
            s2 && not_gate(s1) && s0,
            s2 && s1 && not_gate(s0),
            s2 && s1 && s0
        }
    };
    return result;
}