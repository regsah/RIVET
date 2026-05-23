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

bit_t or_gate(bit_t a, bit_t b)
{
    return not_gate(
        and_gate(
            not_gate(a),
            not_gate(b)
        )
    );
}

bit_t xor_gate(bit_t a, bit_t b)
{
    return or_gate(
        and_gate(a, not_gate(b)),
        and_gate(not_gate(a), b)
    );
}

bit_t nor_gate(bit_t a, bit_t b)
{
    return not_gate(or_gate(a, b));
}

bit_t xnor_gate(bit_t a, bit_t b)
{
    return not_gate(xor_gate(a, b));
}