#include "gates.h"

bit_t and_gate(bit_t i0, bit_t i1)
{
    return not_gate(nand_gate(i0, i1));
}

bit_t and_gate3(bit_t i0, bit_t i1, bit_t i2)
{
    return and_gate(and_gate(i0, i1), i2);
}

bit_t and_gate4(bit_t i0, bit_t i1, bit_t i2, bit_t i3)
{
    return and_gate(and_gate(i0, i1), and_gate(i2, i3));
}

bit_t and_gate8(bit_t i0, bit_t i1, bit_t i2, bit_t i3, bit_t i4, bit_t i5, bit_t i6, bit_t i7)
{
    return and_gate(and_gate4(i0, i1, i2, i3), and_gate4(i4, i5, i6, i7));
}

bit_t and_gate32(word_t I)
{
    return and_gate4(
        and_gate8(I.bits[0], I.bits[1], I.bits[2], I.bits[3], I.bits[4], I.bits[5], I.bits[6], I.bits[7]),
        and_gate8(I.bits[8], I.bits[9], I.bits[10], I.bits[11], I.bits[12], I.bits[13], I.bits[14], I.bits[15]),
        and_gate8(I.bits[16], I.bits[17], I.bits[18], I.bits[19], I.bits[20], I.bits[21], I.bits[22], I.bits[23]),
        and_gate8(I.bits[24], I.bits[25], I.bits[26], I.bits[27], I.bits[28], I.bits[29], I.bits[30], I.bits[31])
    );
}