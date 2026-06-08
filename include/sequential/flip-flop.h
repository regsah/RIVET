#ifndef FLIP_FLOP_H
#define FLIP_FLOP_H

#include "latch.h"

typedef struct
{
    bit_t q;
    bit_t q_bar;
} d_flip_flop_t;

d_flip_flop_t d_flip_flop_init(bit_t q);
d_flip_flop_t d_flip_flop_step(d_flip_flop_t previous, bit_t data);

#endif // FLIP_FLOP_H
