#include "gates.h"

bit_t xnor_gate(bit_t i0, bit_t i1)
{
    return not_gate(xor_gate(i0, i1));
}
