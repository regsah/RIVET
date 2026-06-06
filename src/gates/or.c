#include "gates.h"

bit_t or_gate(bit_t i0, bit_t i1)
{
    return not_gate(
        and_gate(
            not_gate(i0),
            not_gate(i1)
        )
    );
}
