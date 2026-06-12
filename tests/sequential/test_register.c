#include "test.h"

#include <stdint.h>

int test_register1_init()
{
    int fail_counter = 0;

    register1_t reset = register1_init(0);
    ASSERT_EQ_BIT(0, reset.q);
    ASSERT_EQ_BIT(1, reset.q_bar);

    register1_t set = register1_init(1);
    ASSERT_EQ_BIT(1, set.q);
    ASSERT_EQ_BIT(0, set.q_bar);

    if (fail_counter > 0) printf("test_register1_init: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_register1_step()
{
    int fail_counter = 0;

    for (int previous = 0; previous < 2; previous++) {
        for (int data = 0; data < 2; data++) {
            for (int load = 0; load < 2; load++) {
                register1_t reg = register1_init(previous);
                register1_t next = register1_step(reg, data, load);
                bit_t expected = load ? data : previous;

                ASSERT_EQ_BIT(expected, next.q);
                ASSERT_EQ_BIT(not_gate(expected), next.q_bar);
            }
        }
    }

    if (fail_counter > 0) printf("test_register1_step: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_register1_sequence()
{
    int fail_counter = 0;

    register1_t reg = register1_init(0);

    reg = register1_step(reg, 1, 0);
    ASSERT_EQ_BIT(0, reg.q);
    ASSERT_EQ_BIT(1, reg.q_bar);

    reg = register1_step(reg, 1, 1);
    ASSERT_EQ_BIT(1, reg.q);
    ASSERT_EQ_BIT(0, reg.q_bar);

    reg = register1_step(reg, 0, 0);
    ASSERT_EQ_BIT(1, reg.q);
    ASSERT_EQ_BIT(0, reg.q_bar);

    reg = register1_step(reg, 0, 1);
    ASSERT_EQ_BIT(0, reg.q);
    ASSERT_EQ_BIT(1, reg.q_bar);

    if (fail_counter > 0) printf("test_register1_sequence: %d tests failed\n", fail_counter);
    return fail_counter;
}

static word_t word_from_uint32(uint32_t value)
{
    word_t result;
    for (int bit = 0; bit < 32; bit++) {
        result.bits[bit] = (value >> bit) & 1u;
    }
    return result;
}

static void assert_register32_eq_uint32(register32_t reg, uint32_t expected, int *fail_counter)
{
    for (int bit = 0; bit < 32; bit++) {
        ASSERT_EQ_BIT((expected >> bit) & 1u, reg.bits[bit].q);
        ASSERT_EQ_BIT(not_gate((expected >> bit) & 1u), reg.bits[bit].q_bar);
    }
}

int test_register32_init()
{
    int fail_counter = 0;

    register32_t zero = register32_init(word_from_uint32(0x00000000u));
    assert_register32_eq_uint32(zero, 0x00000000u, &fail_counter);

    register32_t pattern = register32_init(word_from_uint32(0xA5C33C5Au));
    assert_register32_eq_uint32(pattern, 0xA5C33C5Au, &fail_counter);

    if (fail_counter > 0) printf("test_register32_init: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_register32_step()
{
    int fail_counter = 0;

    uint32_t previous_values[] = {
        0x00000000u,
        0xFFFFFFFFu,
        0xAAAAAAAAu,
        0x55555555u
    };

    uint32_t data_values[] = {
        0xFFFFFFFFu,
        0x00000000u,
        0x12345678u,
        0x87654321u
    };

    for (int value = 0; value < 4; value++) {
        for (int load = 0; load < 2; load++) {
            register32_t reg = register32_init(word_from_uint32(previous_values[value]));
            register32_t next = register32_step(reg, word_from_uint32(data_values[value]), load);
            uint32_t expected = load ? data_values[value] : previous_values[value];

            assert_register32_eq_uint32(next, expected, &fail_counter);
        }
    }

    if (fail_counter > 0) printf("test_register32_step: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_register32_sequence()
{
    int fail_counter = 0;

    register32_t reg = register32_init(word_from_uint32(0x00000000u));

    reg = register32_step(reg, word_from_uint32(0xDEADBEEFu), 0);
    assert_register32_eq_uint32(reg, 0x00000000u, &fail_counter);

    reg = register32_step(reg, word_from_uint32(0xDEADBEEFu), 1);
    assert_register32_eq_uint32(reg, 0xDEADBEEFu, &fail_counter);

    reg = register32_step(reg, word_from_uint32(0x12345678u), 0);
    assert_register32_eq_uint32(reg, 0xDEADBEEFu, &fail_counter);

    reg = register32_step(reg, word_from_uint32(0x12345678u), 1);
    assert_register32_eq_uint32(reg, 0x12345678u, &fail_counter);

    if (fail_counter > 0) printf("test_register32_sequence: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_register()
{
    int fail_counter = 0;
    fail_counter += test_register1_init();
    fail_counter += test_register1_step();
    fail_counter += test_register1_sequence();
    fail_counter += test_register32_init();
    fail_counter += test_register32_step();
    fail_counter += test_register32_sequence();
    printf("total register tests failed: %d\n", fail_counter);
    return fail_counter;
}
