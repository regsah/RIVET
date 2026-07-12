#include "combinational.h"

bit_t eq1(bit_t i0, bit_t i1)
{
    return not_gate(xor_gate(i0, i1));
}

bit_t eq2(bits2_t I0, bits2_t I1)
{
    return and_gate(
        eq1(I0.bits[0], I1.bits[0]),
        eq1(I0.bits[1], I1.bits[1])
    );
}

bit_t eq4(bits4_t I0, bits4_t I1)
{
    return and_gate4(
        eq1(I0.bits[0], I1.bits[0]),
        eq1(I0.bits[1], I1.bits[1]),
        eq1(I0.bits[2], I1.bits[2]),
        eq1(I0.bits[3], I1.bits[3])
    );
}

bit_t eq8(byte_t I0, byte_t I1)
{
    return and_gate8(
        eq1(I0.bits[0], I1.bits[0]),
        eq1(I0.bits[1], I1.bits[1]),
        eq1(I0.bits[2], I1.bits[2]),
        eq1(I0.bits[3], I1.bits[3]),
        eq1(I0.bits[4], I1.bits[4]),
        eq1(I0.bits[5], I1.bits[5]),
        eq1(I0.bits[6], I1.bits[6]),
        eq1(I0.bits[7], I1.bits[7])
    );
}

bit_t eq32(word_t I0, word_t I1)
{
    word_t comparison;
    for (int bit = 0; bit < 32; bit++) {
        comparison.bits[bit] = eq1(I0.bits[bit], I1.bits[bit]);
    }
    return and_gate32(comparison);
}

bit_t is_zero(bit_t i0)
{
    return eq1(i0, 0);
}

bit_t is_zero2(bits2_t I)
{
    return eq2(I, (bits2_t) {.bits = {0, 0}});
}

bit_t is_zero4(bits4_t I)
{
    return eq4(I, (bits4_t) {.bits = {0, 0, 0, 0}});
}

bit_t is_zero8(byte_t I)
{
    return eq8(I, (byte_t) {.bits = {0, 0, 0, 0, 0, 0, 0, 0}});
}

bit_t is_zero32(word_t I)
{
    return eq32(I, ZERO_WORD);
}
