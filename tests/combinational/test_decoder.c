#include "test.h"

int test_decoder2()
{
    int fail_counter = 0;
    for (int s = 0; s < 2; s++) {
        bits2_t result = decoder2(s);
        for (int bit = 0; bit < 2; bit++) {
            bit_t expected = (s == bit) ? 1 : 0;
            ASSERT_EQ_BIT(expected, result.bits[bit]);
        }
    }
    if (fail_counter > 0) printf("test_decoder2: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_decoder4()
{
    int fail_counter = 0;
    for (int s = 0; s < 4; s++) {
        bits4_t result = decoder4((s >> 0) & 1, (s >> 1) & 1);
        for (int bit = 0; bit < 4; bit++) {
            bit_t expected = (s == bit) ? 1 : 0;
            ASSERT_EQ_BIT(expected, result.bits[bit]);
        }
    }
    if (fail_counter > 0) printf("test_decoder4: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_decoder8()
{
    int fail_counter = 0;
    for (int s = 0; s < 8; s++) {
        byte_t result = decoder8((s >> 0) & 1, (s >> 1) & 1, (s >> 2) & 1);
        for (int bit = 0; bit < 8; bit++) {
            bit_t expected = (s == bit) ? 1 : 0;
            ASSERT_EQ_BIT(expected, result.bits[bit]);
        }
    }
    if (fail_counter > 0) printf("test_decoder8: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_decoder32()
{
    int fail_counter = 0;

    for (int select = 0; select < 32; select++) {
        word_t result = decoder32(
            select & 1, (select >> 1) & 1, (select >> 2) & 1,
            (select >> 3) & 1, (select >> 4) & 1
        );
        for (int bit = 0; bit < 32; bit++) {
            ASSERT_EQ_BIT(bit == select, result.bits[bit]);
        }
    }

    if (fail_counter > 0) printf("test_decoder32: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_decoder()
{
    int fail_counter = 0;
    fail_counter += test_decoder2();
    fail_counter += test_decoder4();
    fail_counter += test_decoder8();
    fail_counter += test_decoder32();
    printf("total decoder tests failed: %d\n", fail_counter);
    return fail_counter;
}
