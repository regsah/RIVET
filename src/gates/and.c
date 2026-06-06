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
