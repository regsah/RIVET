#include "bitwise.h"

#include "combinational.h"

static word_t shift_left_stage(word_t I, int distance, bit_t select)
{
    word_t result;
    for (int bit = 0; bit < distance; bit++) {
        result.bits[bit] = mux2_1(I.bits[bit], 0, select);
    }
    for (int bit = distance; bit < 32; bit++) {
        result.bits[bit] = mux2_1(I.bits[bit], I.bits[bit - distance], select);
    }
    return result;
}

word_t bitwise_sll32(word_t I, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4)
{
    word_t stage0 = shift_left_stage(I, 1, s0);
    word_t stage1 = shift_left_stage(stage0, 2, s1);
    word_t stage2 = shift_left_stage(stage1, 4, s2);
    word_t stage3 = shift_left_stage(stage2, 8, s3);
    return shift_left_stage(stage3, 16, s4);
}
