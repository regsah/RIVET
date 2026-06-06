#include "gates.h"

bit_t nand_gate(bit_t i0, bit_t i1)
{
    return !(i0 && i1);
}
