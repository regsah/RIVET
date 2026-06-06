#include "gates.h"

bit_t xor_gate(bit_t i0, bit_t i1)
{
    return or_gate(
        and_gate(i0, not_gate(i1)),
        and_gate(not_gate(i0), i1)
    );
}
