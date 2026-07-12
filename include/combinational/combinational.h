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

typedef struct
{
    word_t sum;
    bit_t carry;
} adder32_result_t;

bit_t mux2_1(bit_t i0, bit_t i1, bit_t s);
bit_t mux4_1(bit_t i0, bit_t i1, bit_t i2, bit_t i3, bit_t s0, bit_t s1);
bit_t mux8_1(byte_t I, bit_t s0, bit_t s1, bit_t s2);
bit_t mux32_1(word_t I, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4);

bits2_t dmux2_1(bit_t i, bit_t s);
bits4_t dmux4_1(bit_t i, bit_t s0, bit_t s1);
byte_t dmux8_1(bit_t i, bit_t s0, bit_t s1, bit_t s2);
word_t dmux32_1(bit_t i, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4);

adder1_result_t half_adder(bit_t i0, bit_t i1);
adder1_result_t adder1(bit_t i0, bit_t i1, bit_t carry);
adder2_result_t adder2(bits2_t I0, bits2_t I1, bit_t carry);
adder4_result_t adder4(bits4_t I0, bits4_t I1, bit_t carry);
adder8_result_t adder8(byte_t I0, byte_t I1, bit_t carry);
adder32_result_t adder32(word_t I0, word_t I1, bit_t carry);

bits2_t decoder2(bit_t s);
bits4_t decoder4(bit_t s0, bit_t s1);
byte_t decoder8(bit_t s0, bit_t s1, bit_t s2);
word_t decoder32(bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4);

bit_t eq1(bit_t i0, bit_t i1);
bit_t eq2(bits2_t I0, bits2_t I1);
bit_t eq4(bits4_t I0, bits4_t I1);
bit_t eq8(byte_t I0, byte_t I1);
bit_t eq32(word_t I0, word_t I1);

bit_t is_zero(bit_t i0);
bit_t is_zero2(bits2_t I);
bit_t is_zero4(bits4_t I);
bit_t is_zero8(byte_t I);
bit_t is_zero32(word_t I);

#endif // COMBINATIONAL_H
