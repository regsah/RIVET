#ifndef BIT_H
#define BIT_H

#include <stdint.h>

typedef uint8_t bit_t;

typedef struct
{
    bit_t bits[2];
} bits2_t;

typedef struct
{
    bit_t bits[4];
} bits4_t;

typedef struct
{
    bit_t bits[8];
} byte_t;

typedef struct
{
    bit_t bits[32];
} word_t;

static inline int is_valid_bit(bit_t bit)
{
    return bit == 1u || bit == 0u;
}

static inline bit_t normalize_bit(bit_t bit)
{
    return bit ? 1u : 0u;
}

static const word_t ZERO_WORD = {.bits = {0}};

#endif // BIT_H
