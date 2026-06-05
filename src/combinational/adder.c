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