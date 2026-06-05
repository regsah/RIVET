#ifndef COMBINATIONAL_H
#define COMBINATIONAL_H

#include "gates.h"

typedef struct
{
    bit_t sum;
    bit_t carry;
} adder1_result_t;

typedef struct
{
    bits2_t sum;
    bit_t carry;
} adder2_result_t;

typedef struct
{
    bits4_t sum;
    bit_t carry;
} adder4_result_t;

typedef struct
{
    byte_t sum;
    bit_t carry;
} adder8_result_t;

bit_t mux2_1(bit_t i0, bit_t i1, bit_t s);
bit_t mux4_1(bit_t i0, bit_t i1, bit_t i2, bit_t i3, bit_t s0, bit_t s1);
bit_t mux8_1(byte_t I, bit_t s0, bit_t s1, bit_t s2);

bits2_t dmux2_1(bit_t i, bit_t s);
bits4_t dmux4_1(bit_t i, bit_t s0, bit_t s1);
byte_t dmux8_1(bit_t i, bit_t s0, bit_t s1, bit_t s2);

adder1_result_t half_adder(bit_t i0, bit_t i1);
adder1_result_t adder1(bit_t i0, bit_t i1, bit_t carry);
adder2_result_t adder2(bits2_t I0, bits2_t I1, bit_t carry);
adder4_result_t adder4(bits4_t I0, bits4_t I1, bit_t carry);
adder8_result_t adder8(byte_t I0, byte_t I1, bit_t carry);

#endif // COMBINATIONAL_H