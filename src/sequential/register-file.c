#include "register-file.h"

#include "combinational.h"

register_file_t register_file_init(void)
{
    register_file_t result;
    for (int reg = 0; reg < 32; reg++) {
        result.registers[reg] = register32_init(ZERO_WORD);
    }
    return result;
}

word_t register_file_read(
    register_file_t state,
    bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4
)
{
    word_t result;
    for (int bit = 0; bit < 32; bit++) {
        word_t inputs = ZERO_WORD;
        for (int reg = 1; reg < 32; reg++) {
            inputs.bits[reg] = state.registers[reg].bits[bit].q;
        }
        result.bits[bit] = mux32_1(inputs, s0, s1, s2, s3, s4);
    }
    return result;
}

register_file_t register_file_step(
    register_file_t previous, word_t write_data, bit_t write_enable,
    bit_t s0, bit_t s1, bit_t s2, bit_t s3, bit_t s4
)
{
    word_t selected = decoder32(s0, s1, s2, s3, s4);
    register_file_t result;
    result.registers[0] = register32_init(ZERO_WORD);
    for (int reg = 1; reg < 32; reg++) {
        bit_t load = and_gate(selected.bits[reg], write_enable);
        result.registers[reg] = register32_step(previous.registers[reg], write_data, load);
    }
    return result;
}
