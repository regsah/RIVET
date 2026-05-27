#include "test.h"
#include "combinational.h"

int test_mux2_1()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(0, mux2_1(0, 0, 0));
    ASSERT_EQ_BIT(0, mux2_1(0, 0, 1));
    ASSERT_EQ_BIT(0, mux2_1(0, 1, 0));
    ASSERT_EQ_BIT(1, mux2_1(0, 1, 1));
    ASSERT_EQ_BIT(1, mux2_1(1, 0, 0));
    ASSERT_EQ_BIT(0, mux2_1(1, 0, 1));
    ASSERT_EQ_BIT(1, mux2_1(1, 1, 0));
    ASSERT_EQ_BIT(1, mux2_1(1, 1, 1));
    if (fail_counter > 0) printf("test_mux2_1: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_mux4_1()
{
    int fail_counter = 0;
    for (int I = 0; I < 16; I++) {
        for (int S = 0; S < 4; S++) {
            bit_t expected = (I >> S) & 1;
            bit_t actual = mux4_1(
                (I >> 0) & 1,
                (I >> 1) & 1,
                (I >> 2) & 1,
                (I >> 3) & 1,
                (S >> 0) & 1,
                (S >> 1) & 1
            );
            ASSERT_EQ_BIT(expected, actual);
        }
    }
    if (fail_counter > 0) printf("test_mux4_1: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_mux()
{
    int mux_fail_counter = 0;
    mux_fail_counter += test_mux2_1();
    mux_fail_counter += test_mux4_1();
    printf("Total mux tests failed: %d\n", mux_fail_counter);
    return mux_fail_counter;
}