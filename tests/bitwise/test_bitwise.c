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

static int check_bitwise32(uint32_t i0, uint32_t i1)
{
    int fail_counter = 0;
    word_t input0 = word_from_uint32(i0);
    word_t input1 = word_from_uint32(i1);
    word_t and_result = bitwise_and32(input0, input1);
    word_t or_result = bitwise_or32(input0, input1);
    word_t xor_result = bitwise_xor32(input0, input1);
    uint32_t expected_and = i0 & i1;
    uint32_t expected_or = i0 | i1;
    uint32_t expected_xor = i0 ^ i1;

    for (int bit = 0; bit < 32; bit++) {
        ASSERT_EQ_BIT((expected_and >> bit) & 1u, and_result.bits[bit]);
        ASSERT_EQ_BIT((expected_or >> bit) & 1u, or_result.bits[bit]);
        ASSERT_EQ_BIT((expected_xor >> bit) & 1u, xor_result.bits[bit]);
    }
    return fail_counter;
}

int test_bitwise(void)
{
    int fail_counter = 0;
    uint32_t values[] = {
        0u, 0xFFFFFFFFu, 0xAAAAAAAAu, 0x55555555u,
        0x80000000u, 1u, 0x12345678u, 0x87654321u
    };

    for (size_t i0 = 0; i0 < sizeof(values) / sizeof(values[0]); i0++) {
        for (size_t i1 = 0; i1 < sizeof(values) / sizeof(values[0]); i1++) {
            fail_counter += check_bitwise32(values[i0], values[i1]);
        }
    }

    for (int bit0 = 0; bit0 < 32; bit0++) {
        for (int bit1 = 0; bit1 < 32; bit1++) {
            uint32_t i0 = UINT32_C(1) << bit0;
            uint32_t i1 = UINT32_C(1) << bit1;
            fail_counter += check_bitwise32(i0, i1);
            fail_counter += check_bitwise32(~i0, ~i1);
        }
    }

    printf("total bitwise tests failed: %d\n", fail_counter);
    return fail_counter;
}
