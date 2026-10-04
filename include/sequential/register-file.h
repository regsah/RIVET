#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include "register.h"

typedef struct
{
    register32_t registers[32];
} register_file_t;

register_file_t register_file_init(void);

word_t register_file_read(
    register_file_t state,
    bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4
);

register_file_t register_file_step(
    register_file_t previous, word_t write_data, bit_t write_enable,
    bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4
);

#endif
