#include "test.h"

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

int test_register()
{
    int fail_counter = 0;
    fail_counter += test_register1_init();
    fail_counter += test_register1_step();
    fail_counter += test_register1_sequence();
    printf("total register tests failed: %d\n", fail_counter);
    return fail_counter;
}
