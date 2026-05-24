#ifndef COMBINATIONAL_H
#define COMBINATIONAL_H

#include "gates.h"

bit_t mux2_1(bit_t i0, bit_t i1, bit_t s);
bit_t mux4_1(bit_t i0, bit_t i1, bit_t i2, bit_t i3, bit_t s0, bit_t s1);
bit_t mux8_1(byte_t I, bit_t s0, bit_t s1, bit_t s2);

#endif // COMBINATIONAL_H