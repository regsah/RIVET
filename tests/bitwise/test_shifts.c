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

static int check_shifts32(uint32_t value, int amount)
{
    int fail_counter = 0;
    word_t input = word_from_uint32(value);
    bit_t s0 = amount & 1;
    bit_t s1 = (amount >> 1) & 1;
    bit_t s2 = (amount >> 2) & 1;
    bit_t s3 = (amount >> 3) & 1;
    bit_t s4 = (amount >> 4) & 1;
    word_t left = bitwise_sll32(input, s0, s1, s2, s3, s4);
    uint32_t expected_left = value << amount;

    for (int bit = 0; bit < 32; bit++) {
        ASSERT_EQ_BIT((expected_left >> bit) & 1u, left.bits[bit]);
    }
    return fail_counter;
}

int test_shifts(void)
{
    int fail_counter = 0;
    uint32_t values[] = {
        0u, 0xFFFFFFFFu, 0xAAAAAAAAu, 0x55555555u,
        0x80000000u, 0x7FFFFFFFu, 0x12345678u, 0x87654321u
    };

    for (int amount = 0; amount < 32; amount++) {
        for (size_t value = 0; value < sizeof(values) / sizeof(values[0]); value++) {
            fail_counter += check_shifts32(values[value], amount);
        }
        for (int bit = 0; bit < 32; bit++) {
            uint32_t value = UINT32_C(1) << bit;
            fail_counter += check_shifts32(value, amount);
            fail_counter += check_shifts32(~value, amount);
        }
    }

    printf("total shift tests failed: %d\n", fail_counter);
    return fail_counter;
}
