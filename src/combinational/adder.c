#include "combinational.h"

adder1_result_t half_adder(bit_t i0, bit_t i1)
{
    adder1_result_t result;
    result.sum = xor_gate(i0, i1);
    result.carry = and_gate(i0, i1);
    return result;
}

adder1_result_t adder1(bit_t i0, bit_t i1, bit_t carry)
{
    adder1_result_t first_half = half_adder(i0, i1);
    adder1_result_t second_half = half_adder(first_half.sum, carry);

    adder1_result_t result;
    result.sum = second_half.sum;
    result.carry = or_gate(first_half.carry, second_half.carry);
    return result;
}

adder2_result_t adder2(bits2_t I0, bits2_t I1, bit_t carry)
{
    adder1_result_t first_bit = adder1(I0.bits[0], I1.bits[0], carry);
    adder1_result_t second_bit = adder1(I0.bits[1], I1.bits[1], first_bit.carry);

    adder2_result_t result;
    result.sum = (bits2_t) {.bits = {first_bit.sum, second_bit.sum}};
    result.carry = second_bit.carry;
    return result;
}

adder4_result_t adder4(bits4_t I0, bits4_t I1, bit_t carry)
{
    adder1_result_t bit0 = adder1(I0.bits[0], I1.bits[0], carry);
    adder1_result_t bit1 = adder1(I0.bits[1], I1.bits[1], bit0.carry);
    adder1_result_t bit2 = adder1(I0.bits[2], I1.bits[2], bit1.carry);
    adder1_result_t bit3 = adder1(I0.bits[3], I1.bits[3], bit2.carry);

    adder4_result_t result;
    result.sum = (bits4_t) {.bits = {bit0.sum, bit1.sum, bit2.sum, bit3.sum}};
    result.carry = bit3.carry;
    return result;
}

adder8_result_t adder8(byte_t I0, byte_t I1, bit_t carry)
{
    adder1_result_t bit0 = adder1(I0.bits[0], I1.bits[0], carry);
    adder1_result_t bit1 = adder1(I0.bits[1], I1.bits[1], bit0.carry);
    adder1_result_t bit2 = adder1(I0.bits[2], I1.bits[2], bit1.carry);
    adder1_result_t bit3 = adder1(I0.bits[3], I1.bits[3], bit2.carry);
    adder1_result_t bit4 = adder1(I0.bits[4], I1.bits[4], bit3.carry);
    adder1_result_t bit5 = adder1(I0.bits[5], I1.bits[5], bit4.carry);
    adder1_result_t bit6 = adder1(I0.bits[6], I1.bits[6], bit5.carry);
    adder1_result_t bit7 = adder1(I0.bits[7], I1.bits[7], bit6.carry);

    adder8_result_t result;
    result.sum = (byte_t) {.bits = {bit0.sum, bit1.sum, bit2.sum, bit3.sum, bit4.sum, bit5.sum, bit6.sum, bit7.sum}};
    result.carry = bit7.carry;
    return result;
}

adder32_result_t adder32(word_t I0, word_t I1, bit_t carry)
{
    adder8_result_t byte0 = adder8(
        (byte_t) {.bits = {I0.bits[0], I0.bits[1], I0.bits[2], I0.bits[3], I0.bits[4], I0.bits[5], I0.bits[6], I0.bits[7]}},
        (byte_t) {.bits = {I1.bits[0], I1.bits[1], I1.bits[2], I1.bits[3], I1.bits[4], I1.bits[5], I1.bits[6], I1.bits[7]}},
        carry
    );

    adder8_result_t byte1 = adder8(
        (byte_t) {.bits = {I0.bits[8], I0.bits[9], I0.bits[10], I0.bits[11], I0.bits[12], I0.bits[13], I0.bits[14], I0.bits[15]}},
        (byte_t) {.bits = {I1.bits[8], I1.bits[9], I1.bits[10], I1.bits[11], I1.bits[12], I1.bits[13], I1.bits[14], I1.bits[15]}},
        byte0.carry
    );

    adder8_result_t byte2 = adder8(
        (byte_t) {.bits = {I0.bits[16], I0.bits[17], I0.bits[18], I0.bits[19], I0.bits[20], I0.bits[21], I0.bits[22], I0.bits[23]}},
        (byte_t) {.bits = {I1.bits[16], I1.bits[17], I1.bits[18], I1.bits[19], I1.bits[20], I1.bits[21], I1.bits[22], I1.bits[23]}},
        byte1.carry
    );

    adder8_result_t byte3 = adder8(
        (byte_t) {.bits = {I0.bits[24], I0.bits[25], I0.bits[26], I0.bits[27], I0.bits[28], I0.bits[29], I0.bits[30], I0.bits[31]}},
        (byte_t) {.bits = {I1.bits[24], I1.bits[25], I1.bits[26], I1.bits[27], I1.bits[28], I1.bits[29], I1.bits[30], I1.bits[31]}},
        byte2.carry
    );

    adder32_result_t result;
    for (int bit = 0; bit < 8; bit++) {
        result.sum.bits[bit] = byte0.sum.bits[bit];
        result.sum.bits[bit + 8] = byte1.sum.bits[bit];
        result.sum.bits[bit + 16] = byte2.sum.bits[bit];
        result.sum.bits[bit + 24] = byte3.sum.bits[bit];
    }
    result.carry = byte3.carry;
    return result;
}