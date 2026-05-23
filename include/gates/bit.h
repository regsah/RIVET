#ifndef BIT_H
#define BIT_H

#include <stdint.h>

typedef uint8_t bit_t;

static inline int is_valid_bit(bit_t bit)
{
    return bit == 1u || bit == 0u;
}

static inline bit_t normalize_bit(bit_t bit)
{
    return bit ? 1u : 0u;
}

#endif // BIT_H
