#include "test.h"

int test_dmux2_1()
{
    int fail_counter = 0;

    for (int input = 0; input < 2; input++) {
        for (int select = 0; select < 2; select++) {
            bits2_t out = dmux2_1(input, select);
            for (int bit = 0; bit < 2; bit++) {
                bit_t expected = input && (bit == select);
                ASSERT_EQ_BIT(expected, out.bits[bit]);
            }
        }
    }

    if (fail_counter > 0) {
        printf("test_dmux2_1: %d tests failed\n", fail_counter);
    }

    return fail_counter;
}

int test_dmux4_1()
{
    int fail_counter = 0;

    for (int input = 0; input < 2; input++) {
        for (int select = 0; select < 4; select++) {
            bits4_t out = dmux4_1(
                input,
                (select >> 0) & 1,
                (select >> 1) & 1
            );
            for (int bit = 0; bit < 4; bit++) {
                bit_t expected = input && (bit == select);
                ASSERT_EQ_BIT(expected, out.bits[bit]);
            }
        }
    }

    if (fail_counter > 0) {
        printf("test_dmux4_1: %d tests failed\n", fail_counter);
    }

    return fail_counter;
}

int test_dmux8_1()
{
    int fail_counter = 0;

    for (int input = 0; input < 2; input++) {
        for (int select = 0; select < 8; select++) {
            byte_t out = dmux8_1(
                input,
                (select >> 0) & 1,
                (select >> 1) & 1,
                (select >> 2) & 1
            );
            for (int bit = 0; bit < 8; bit++) {
                bit_t expected = input && (bit == select);
                ASSERT_EQ_BIT(expected, out.bits[bit]);
            }
        }
    }

    if (fail_counter > 0) {
        printf("test_dmux8_1: %d tests failed\n", fail_counter);
    }

    return fail_counter;
}

int test_dmux()
{
    int dmux_fail_counter = 0;
    dmux_fail_counter += test_dmux2_1();
    dmux_fail_counter += test_dmux4_1();
    dmux_fail_counter += test_dmux8_1();
    printf("Total dmux tests failed: %d\n", dmux_fail_counter);
    return dmux_fail_counter;
}