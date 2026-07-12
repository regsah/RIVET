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

int test_mux8_1()
{
    int fail_counter = 0;
    for (int I = 0; I < 256; I++) {
        for (int S = 0; S < 8; S++) {
            bit_t expected = (I >> S) & 1;
            byte_t input = { .bits = {
                (I >> 0) & 1,
                (I >> 1) & 1,
                (I >> 2) & 1,
                (I >> 3) & 1,
                (I >> 4) & 1,
                (I >> 5) & 1,
                (I >> 6) & 1,
                (I >> 7) & 1
            }};
            bit_t actual = mux8_1(
                input,
                (S >> 0) & 1,
                (S >> 1) & 1,
                (S >> 2) & 1
            );
            ASSERT_EQ_BIT(expected, actual);
        }
    }
    if (fail_counter > 0) printf("test_mux8_1: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_mux32_1()
{
    int fail_counter = 0;
    word_t input = word_from_uint32(0xA5C33C5Au);

    for (int select = 0; select < 32; select++) {
        ASSERT_EQ_BIT(
            input.bits[select],
            mux32_1(input, select & 1, (select >> 1) & 1, (select >> 2) & 1,
                    (select >> 3) & 1, (select >> 4) & 1)
        );
    }

    if (fail_counter > 0) printf("test_mux32_1: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_mux()
{
    int mux_fail_counter = 0;
    mux_fail_counter += test_mux2_1();
    mux_fail_counter += test_mux4_1();
    mux_fail_counter += test_mux8_1();
    mux_fail_counter += test_mux32_1();
    printf("Total mux tests failed: %d\n", mux_fail_counter);
    return mux_fail_counter;
}
