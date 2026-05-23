#include "gates.h"

bit_t nand_gate(bit_t a, bit_t b)
{
    return !(a && b);
}