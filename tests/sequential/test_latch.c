#include "test.h"

int test_sr_latch_init()
{
    int fail_counter = 0;

    sr_latch_t reset = sr_latch_init(0);
    ASSERT_EQ_BIT(0, reset.q);
    ASSERT_EQ_BIT(1, reset.q_bar);

    sr_latch_t set = sr_latch_init(1);
    ASSERT_EQ_BIT(1, set.q);
    ASSERT_EQ_BIT(0, set.q_bar);

    if (fail_counter > 0) printf("test_sr_latch_init: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_sr_latch_step()
{
    int fail_counter = 0;

    sr_latch_t latch = sr_latch_init(0);

    latch = sr_latch_step(latch, 1, 0);
    latch = sr_latch_step(latch, 1, 0);
    ASSERT_EQ_BIT(1, latch.q);
    ASSERT_EQ_BIT(0, latch.q_bar);

    latch = sr_latch_step(latch, 0, 0);
    ASSERT_EQ_BIT(1, latch.q);
    ASSERT_EQ_BIT(0, latch.q_bar);

    latch = sr_latch_step(latch, 0, 1);
    latch = sr_latch_step(latch, 0, 1);
    ASSERT_EQ_BIT(0, latch.q);
    ASSERT_EQ_BIT(1, latch.q_bar);

    latch = sr_latch_step(latch, 0, 0);
    ASSERT_EQ_BIT(0, latch.q);
    ASSERT_EQ_BIT(1, latch.q_bar);

    latch = sr_latch_step(latch, 1, 1);
    ASSERT_EQ_BIT(0, latch.q);
    ASSERT_EQ_BIT(0, latch.q_bar);

    if (fail_counter > 0) printf("test_sr_latch_step: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_d_latch_step()
{
    int fail_counter = 0;

    sr_latch_t latch = sr_latch_init(0);

    latch = d_latch_step(latch, 1, 0);
    ASSERT_EQ_BIT(0, latch.q);
    ASSERT_EQ_BIT(1, latch.q_bar);

    latch = d_latch_step(latch, 1, 1);
    latch = d_latch_step(latch, 1, 1);
    ASSERT_EQ_BIT(1, latch.q);
    ASSERT_EQ_BIT(0, latch.q_bar);

    latch = d_latch_step(latch, 0, 0);
    ASSERT_EQ_BIT(1, latch.q);
    ASSERT_EQ_BIT(0, latch.q_bar);

    latch = d_latch_step(latch, 0, 1);
    latch = d_latch_step(latch, 0, 1);
    ASSERT_EQ_BIT(0, latch.q);
    ASSERT_EQ_BIT(1, latch.q_bar);

    if (fail_counter > 0) printf("test_d_latch_step: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_latch()
{
    int fail_counter = 0;
    fail_counter += test_sr_latch_init();
    fail_counter += test_sr_latch_step();
    fail_counter += test_d_latch_step();
    printf("total latch tests failed: %d\n", fail_counter);
    return fail_counter;
}
