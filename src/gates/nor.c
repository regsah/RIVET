#include "gates.h"

bit_t nor_gate(bit_t i0, bit_t i1)
{
    return not_gate(or_gate(i0, i1));
}
