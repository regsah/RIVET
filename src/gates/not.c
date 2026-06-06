#include "gates.h"

bit_t not_gate(bit_t i0)
{
    return nand_gate(i0, i0);
}
