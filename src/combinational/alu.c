#include "alu.h"

#include "bitwise.h"
#include "combinational.h"

word_t alu32(word_t I0, word_t I1, bit_t op0, bit_t op1, bit_t op2, bit_t op3)
{
    adder32_result_t arithmetic = add_sub32(I0, I1, op3);
    word_t left = bitwise_sll32(I0, I1.bits[0], I1.bits[1], I1.bits[2], I1.bits[3], I1.bits[4]);
    word_t right = bitwise_srl32(I0, I1.bits[0], I1.bits[1], I1.bits[2], I1.bits[3], I1.bits[4]);
    word_t arithmetic_right = bitwise_sra32(I0, I1.bits[0], I1.bits[1], I1.bits[2], I1.bits[3], I1.bits[4]);
    word_t signed_less = ZERO_WORD;
    word_t unsigned_less = ZERO_WORD;
    signed_less.bits[0] = lt32_signed(I0, I1);
    unsigned_less.bits[0] = lt32_unsigned(I0, I1);
    word_t xor_result = bitwise_xor32(I0, I1);
    word_t or_result = bitwise_or32(I0, I1);
    word_t and_result = bitwise_and32(I0, I1);

    word_t result;
    for (int bit = 0; bit < 32; bit++) {
        bit_t lower = mux8_1(
            (byte_t) {.bits = {
                arithmetic.sum.bits[bit], left.bits[bit],
                signed_less.bits[bit], unsigned_less.bits[bit],
                xor_result.bits[bit], right.bits[bit],
                or_result.bits[bit], and_result.bits[bit]
            }},
            op0, op1, op2
        );
        bit_t upper = mux8_1(
            (byte_t) {.bits = {
                arithmetic.sum.bits[bit], 0, 0, 0,
                0, arithmetic_right.bits[bit], 0, 0
            }},
            op0, op1, op2
        );
        result.bits[bit] = mux2_1(lower, upper, op3);
    }
    return result;
}
