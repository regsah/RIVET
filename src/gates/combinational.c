#include "combinational.h"

bit_t mux2_1(bit_t i0, bit_t i1, bit_t s)
{
    return or_gate(
        and_gate(not_gate(s), i0),
        and_gate(s, i1)
    );
}


bit_t mux4_1(bit_t i0, bit_t i1, bit_t i2, bit_t i3, bit_t s0, bit_t s1)
{
    return mux2_1(
        mux2_1(i0, i1, s0),
        mux2_1(i2, i3, s0),
        s1
    );
}

bit_t mux8_1(byte_t I, bit_t s0, bit_t s1, bit_t s2)
{
    return mux2_1(
        mux4_1(I.bits[0], I.bits[1], I.bits[2], I.bits[3], s0, s1),
        mux4_1(I.bits[4], I.bits[5], I.bits[6], I.bits[7], s0, s1),
        s2
    );
}
