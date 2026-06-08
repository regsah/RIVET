#ifndef LATCH_H
#define LATCH_H

#include "gates.h"

typedef struct
{
    bit_t q;
    bit_t q_bar;
} sr_latch_t;

typedef struct
{
    bit_t q;
    bit_t q_bar;
} d_latch_t;

sr_latch_t sr_latch_init(bit_t q);
sr_latch_t sr_latch_step(sr_latch_t previous, bit_t set, bit_t reset);

d_latch_t d_latch_init(bit_t q);
d_latch_t d_latch_step(d_latch_t previous, bit_t data, bit_t enable);

#endif // LATCH_H
