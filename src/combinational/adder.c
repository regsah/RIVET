#include "combinational.h"

adder_result_t half_adder(bit_t i0, bit_t i1)
{
    adder_result_t result;
    result.sum = xor_gate(i0, i1);
    result.carry = and_gate(i0, i1);
    return result;
}

adder_result_t adder(bit_t i0, bit_t i1, bit_t carry)
{
    adder_result_t first_half = half_adder(i0, i1);
    adder_result_t second_half = half_adder(first_half.sum, carry);

    adder_result_t result;
    result.sum = second_half.sum;
    result.carry = or_gate(first_half.carry, second_half.carry);
    return result;
}

adder2_result_t adder2(bits2_t I0, bits2_t I1, bit_t carry)
{
    adder_result_t first_bit = adder(I0.bits[0], I1.bits[0], carry);
    adder_result_t second_bit = adder(I0.bits[1], I1.bits[1], first_bit.carry);

    adder2_result_t result;
    result.sum = (bits2_t) {.bits = {first_bit.sum, second_bit.sum}};
    result.carry = second_bit.carry;
    return result;
}

adder4_result_t adder4(bits4_t I0, bits4_t I1, bit_t carry)
{
    adder_result_t bit0 = adder(I0.bits[0], I1.bits[0], carry);
    adder_result_t bit1 = adder(I0.bits[1], I1.bits[1], bit0.carry);
    adder_result_t bit2 = adder(I0.bits[2], I1.bits[2], bit1.carry);
    adder_result_t bit3 = adder(I0.bits[3], I1.bits[3], bit2.carry);

    adder4_result_t result;
    result.sum = (bits4_t) {.bits = {bit0.sum, bit1.sum, bit2.sum, bit3.sum}};
    result.carry = bit3.carry;
    return result;
}

adder8_result_t adder8(byte_t I0, byte_t I1, bit_t carry)
{
    adder_result_t bit0 = adder(I0.bits[0], I1.bits[0], carry);
    adder_result_t bit1 = adder(I0.bits[1], I1.bits[1], bit0.carry);
    adder_result_t bit2 = adder(I0.bits[2], I1.bits[2], bit1.carry);
    adder_result_t bit3 = adder(I0.bits[3], I1.bits[3], bit2.carry);
    adder_result_t bit4 = adder(I0.bits[4], I1.bits[4], bit3.carry);
    adder_result_t bit5 = adder(I0.bits[5], I1.bits[5], bit4.carry);
    adder_result_t bit6 = adder(I0.bits[6], I1.bits[6], bit5.carry);
    adder_result_t bit7 = adder(I0.bits[7], I1.bits[7], bit6.carry);

    adder8_result_t result;
    result.sum = (byte_t) {.bits = {bit0.sum, bit1.sum, bit2.sum, bit3.sum, bit4.sum, bit5.sum, bit6.sum, bit7.sum}};
    result.carry = bit7.carry;
    return result;
}