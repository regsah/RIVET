#include "gates.h"

bit_t nand_gate(bit_t a, bit_t b)
{
    return !(a && b);
}

bit_t not_gate(bit_t a)
{
    return nand_gate(a, a);
}

bit_t and_gate(bit_t a, bit_t b)
{
    return not_gate(nand_gate(a, b));
}

