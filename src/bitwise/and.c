#include "bitwise.h"

#include "gates.h"

word_t bitwise_and32(word_t I0, word_t I1)
{
    word_t result;
    for (int bit = 0; bit < 32; bit++) {
        result.bits[bit] = and_gate(I0.bits[bit], I1.bits[bit]);
    }
    return result;
}
