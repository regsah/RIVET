#ifndef BITWISE_H
#define BITWISE_H

#include "bit.h"

word_t bitwise_and32(word_t I0, word_t I1);
word_t bitwise_or32(word_t I0, word_t I1);
word_t bitwise_xor32(word_t I0, word_t I1);

word_t bitwise_sll32(word_t I, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4);
word_t bitwise_srl32(word_t I, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4);

#endif
