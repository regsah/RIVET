#include "test.h"

#include <stdint.h>

static word_t word_from_uint32(uint32_t value)
{
    word_t result;
    for (int bit = 0; bit < 32; bit++) {
        result.bits[bit] = (value >> bit) & 1u;
    }
    return result;
}

static word_t read_register(register_file_t state, int address)
{
    return register_file_read(
        state, address & 1, (address >> 1) & 1, (address >> 2) & 1,
        (address >> 3) & 1, (address >> 4) & 1
    );
}

static register_file_t write_register(
    register_file_t previous, int address, uint32_t data, bit_t enable
)
{
    return register_file_step(
        previous, word_from_uint32(data), enable,
        address & 1, (address >> 1) & 1, (address >> 2) & 1,
        (address >> 3) & 1, (address >> 4) & 1
    );
}

static int check_register_file(register_file_t state, const uint32_t expected[32])
{
    int fail_counter = 0;
    for (int reg = 0; reg < 32; reg++) {
        word_t actual = read_register(state, reg);
        for (int bit = 0; bit < 32; bit++) {
            bit_t expected_bit = (expected[reg] >> bit) & 1u;
            ASSERT_EQ_BIT(expected_bit, actual.bits[bit]);
            ASSERT_EQ_BIT(expected_bit, state.registers[reg].bits[bit].q);
            ASSERT_EQ_BIT(expected_bit ^ 1u, state.registers[reg].bits[bit].q_bar);
        }
    }
    return fail_counter;
}

static int test_register_file_read(void)
{
    int fail_counter = 0;
    register_file_t state = register_file_init();
    uint32_t expected[32] = {0};
    fail_counter += check_register_file(state, expected);

    for (int inverted = 0; inverted < 2; inverted++) {
        for (int reg = 1; reg < 32; reg++) {
            uint32_t pattern = UINT32_C(1) << reg;
            expected[reg] = inverted ? ~pattern : pattern;
            state.registers[reg] = register32_init(word_from_uint32(expected[reg]));
        }
        fail_counter += check_register_file(state, expected);

        for (int first = 0; first < 32; first++) {
            for (int second = 0; second < 32; second++) {
                word_t a = read_register(state, first);
                word_t b = read_register(state, second);
                for (int bit = 0; bit < 32; bit++) {
                    ASSERT_EQ_BIT((expected[first] >> bit) & 1u, a.bits[bit]);
                    ASSERT_EQ_BIT((expected[second] >> bit) & 1u, b.bits[bit]);
                }
            }
        }
    }
    return fail_counter;
}

static int test_register_file_write(void)
{
    int fail_counter = 0;
    register_file_t state = register_file_init();
    uint32_t expected[32] = {0};

    for (int pass = 0; pass < 2; pass++) {
        for (int address = 0; address < 32; address++) {
            uint32_t data = (UINT32_C(1) << address) ^ UINT32_C(0xA5C33C5A);
            if (pass) data = ~data;

            register_file_t held = write_register(state, address, data, 0);
            fail_counter += check_register_file(held, expected);

            register_file_t next = write_register(state, address, data, 1);
            fail_counter += check_register_file(state, expected);
            if (address != 0) expected[address] = data;
            fail_counter += check_register_file(next, expected);
            state = next;
        }
    }
    return fail_counter;
}

int test_register_file(void)
{
    int fail_counter = 0;
    fail_counter += test_register_file_read();
    fail_counter += test_register_file_write();
    printf("total register file tests failed: %d\n", fail_counter);
    return fail_counter;
}
