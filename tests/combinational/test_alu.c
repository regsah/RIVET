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

static int64_t signed_value(uint32_t value)
{
    return value <= INT32_MAX ? (int64_t)value : (int64_t)value - INT64_C(0x100000000);
}

static uint32_t expected_alu32(uint32_t i0, uint32_t i1, int operation)
{
    unsigned amount = i1 & 31u;
    switch (operation) {
        case 0: return i0 + i1;
        case 1: return i0 << amount;
        case 2: return signed_value(i0) < signed_value(i1);
        case 3: return i0 < i1;
        case 4: return i0 ^ i1;
        case 5: return i0 >> amount;
        case 6: return i0 | i1;
        case 7: return i0 & i1;
        case 8: return i0 - i1;
        case 13: {
            uint32_t result = i0 >> amount;
            if (amount > 0 && (i0 & UINT32_C(0x80000000))) {
                result |= UINT32_MAX << (32 - amount);
            }
            return result;
        }
        default: return 0;
    }
}

static int check_alu32(uint32_t i0, uint32_t i1, int operation)
{
    int fail_counter = 0;
    uint32_t expected = expected_alu32(i0, i1, operation);
    word_t actual = alu32(
        word_from_uint32(i0), word_from_uint32(i1),
        operation & 1, (operation >> 1) & 1,
        (operation >> 2) & 1, (operation >> 3) & 1
    );

    for (int bit = 0; bit < 32; bit++) {
        ASSERT_EQ_BIT((expected >> bit) & 1u, actual.bits[bit]);
    }
    return fail_counter;
}

int test_alu(void)
{
    int fail_counter = 0;
    uint32_t values[] = {
        0u, 1u, 0xFFFFFFFFu, 0x7FFFFFFFu, 0x80000000u,
        0xAAAAAAAAu, 0x55555555u, 0x12345678u, 0x87654321u,
        0xFFu, 0x100u, 0x10000u
    };

    for (size_t i0 = 0; i0 < sizeof(values) / sizeof(values[0]); i0++) {
        for (size_t i1 = 0; i1 < sizeof(values) / sizeof(values[0]); i1++) {
            for (int operation = 0; operation < 16; operation++) {
                fail_counter += check_alu32(values[i0], values[i1], operation);
            }
        }
    }

    int shift_operations[] = {1, 5, 13};
    for (unsigned amount = 0; amount < 32; amount++) {
        for (size_t value = 0; value < sizeof(values) / sizeof(values[0]); value++) {
            for (size_t operation = 0; operation < sizeof(shift_operations) / sizeof(shift_operations[0]); operation++) {
                fail_counter += check_alu32(values[value], amount, shift_operations[operation]);
                fail_counter += check_alu32(values[value], amount | UINT32_C(0xFFFFFFE0), shift_operations[operation]);
            }
        }
    }

    for (int bit = 0; bit < 32; bit++) {
        uint32_t value = UINT32_C(1) << bit;
        for (int operation = 0; operation < 16; operation++) {
            fail_counter += check_alu32(value, ~value, operation);
            fail_counter += check_alu32(~value, value, operation);
            fail_counter += check_alu32(value, value, operation);
        }
    }

    printf("total ALU tests failed: %d\n", fail_counter);
    return fail_counter;
}
