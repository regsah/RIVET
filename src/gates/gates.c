#include "gates.h"

bit_t nand_gate(bit_t i0, bit_t i1)
{
    return !(i0 && i1);
}

bit_t not_gate(bit_t i0)
{
    return nand_gate(i0, i0);
}

bit_t and_gate(bit_t i0, bit_t i1)
{
    return not_gate(nand_gate(i0, i1));
}

bit_t or_gate(bit_t i0, bit_t i1)
{
    return not_gate(
        and_gate(
            not_gate(i0),
            not_gate(i1)
        )
    );
}

bit_t xor_gate(bit_t i0, bit_t i1)
{
    return or_gate(
        and_gate(i0, not_gate(i1)),
        and_gate(not_gate(i0), i1)
    );
}

bit_t nor_gate(bit_t i0, bit_t i1)
{
    return not_gate(or_gate(i0, i1));
}

bit_t xnor_gate(bit_t i0, bit_t i1)
{
    return not_gate(xor_gate(i0, i1));
}