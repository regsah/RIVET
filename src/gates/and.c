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