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

static word_t shift_right_stage(word_t I, int distance, bit_t select, bit_t fill)
{
    word_t result;
    for (int bit = 0; bit < 32 - distance; bit++) {
        result.bits[bit] = mux2_1(I.bits[bit], I.bits[bit + distance], select);
    }
    for (int bit = 32 - distance; bit < 32; bit++) {
        result.bits[bit] = mux2_1(I.bits[bit], fill, select);
    }
    return result;
}

static word_t shift_right_stages(
    word_t I, bit_t fill,
    bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4
)
{
    word_t stage0 = shift_right_stage(I, 1, s0, fill);
    word_t stage1 = shift_right_stage(stage0, 2, s1, fill);
    word_t stage2 = shift_right_stage(stage1, 4, s2, fill);
    word_t stage3 = shift_right_stage(stage2, 8, s3, fill);
    return shift_right_stage(stage3, 16, s4, fill);
}

word_t bitwise_sll32(word_t I, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4)
{
    word_t stage0 = shift_left_stage(I, 1, s0);
    word_t stage1 = shift_left_stage(stage0, 2, s1);
    word_t stage2 = shift_left_stage(stage1, 4, s2);
    word_t stage3 = shift_left_stage(stage2, 8, s3);
    return shift_left_stage(stage3, 16, s4);
}

word_t bitwise_srl32(word_t I, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4)
{
    return shift_right_stages(I, 0, s0, s1, s2, s3, s4);
}

word_t bitwise_sra32(word_t I, bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4)
{
    return shift_right_stages(I, I.bits[31], s0, s1, s2, s3, s4);
}
