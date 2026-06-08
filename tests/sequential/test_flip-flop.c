#include "test.h"

int test_d_flip_flop_init()
{
    int fail_counter = 0;

    d_flip_flop_t reset = d_flip_flop_init(0);
    ASSERT_EQ_BIT(0, reset.q);
    ASSERT_EQ_BIT(1, reset.q_bar);

    d_flip_flop_t set = d_flip_flop_init(1);
    ASSERT_EQ_BIT(1, set.q);
    ASSERT_EQ_BIT(0, set.q_bar);

    if (fail_counter > 0) printf("test_d_flip_flop_init: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_d_flip_flop_step()
{
    int fail_counter = 0;

    for (int previous = 0; previous < 2; previous++) {
        for (int data = 0; data < 2; data++) {
            d_flip_flop_t flip_flop = d_flip_flop_init(previous);
            d_flip_flop_t next = d_flip_flop_step(flip_flop, data);

            ASSERT_EQ_BIT(data, next.q);
            ASSERT_EQ_BIT(not_gate(data), next.q_bar);
        }
    }

    if (fail_counter > 0) printf("test_d_flip_flop_step: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_d_flip_flop_sequence()
{
    int fail_counter = 0;

    d_flip_flop_t flip_flop = d_flip_flop_init(0);

    flip_flop = d_flip_flop_step(flip_flop, 1);
    ASSERT_EQ_BIT(1, flip_flop.q);
    ASSERT_EQ_BIT(0, flip_flop.q_bar);

    flip_flop = d_flip_flop_step(flip_flop, 1);
    ASSERT_EQ_BIT(1, flip_flop.q);
    ASSERT_EQ_BIT(0, flip_flop.q_bar);

    flip_flop = d_flip_flop_step(flip_flop, 0);
    ASSERT_EQ_BIT(0, flip_flop.q);
    ASSERT_EQ_BIT(1, flip_flop.q_bar);

    flip_flop = d_flip_flop_step(flip_flop, 0);
    ASSERT_EQ_BIT(0, flip_flop.q);
    ASSERT_EQ_BIT(1, flip_flop.q_bar);

    if (fail_counter > 0) printf("test_d_flip_flop_sequence: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_flip_flop()
{
    int fail_counter = 0;
    fail_counter += test_d_flip_flop_init();
    fail_counter += test_d_flip_flop_step();
    fail_counter += test_d_flip_flop_sequence();
    printf("total flip-flop tests failed: %d\n", fail_counter);
    return fail_counter;
}
