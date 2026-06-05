#include "combinational.h"

adder_result_t half_adder(bit_t i0, bit_t i1)
{
    return (adder_result_t){
        .sum = xor_gate(i0, i1),
        .carry = and_gate(i0, i1)
    };
}