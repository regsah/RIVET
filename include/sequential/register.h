#ifndef REGISTER_H
#define REGISTER_H

#include "flip-flop.h"

typedef struct
{
    bit_t q;
    bit_t q_bar;
} register1_t;

register1_t register1_init(bit_t q);
register1_t register1_step(register1_t previous, bit_t data, bit_t load);

#endif // REGISTER_H
