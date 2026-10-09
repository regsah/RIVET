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

int test_half_adder()
{
    int fail_counter = 0;
    for (int i0 = 0; i0 < 2; i0++) {
        for (int i1 = 0; i1 < 2; i1++) {
            adder1_result_t result = half_adder(i0, i1);
            ASSERT_EQ_BIT((i0 ^ i1) & 1, result.sum);
            ASSERT_EQ_BIT((i0 & i1) & 1, result.carry);
        }
    }
    return fail_counter;
}

int test_adder1()
{
    int fail_counter = 0;
    for (int i0 = 0; i0 < 2; i0++) {
        for (int i1 = 0; i1 < 2; i1++) {
            for (int carry = 0; carry < 2; carry++) {
                adder1_result_t result = adder1(i0, i1, carry);
                ASSERT_EQ_BIT((i0 ^ i1 ^ carry) & 1, result.sum);
                ASSERT_EQ_BIT(((i0 & i1) | (carry & (i0 ^ i1))) & 1, result.carry);
            }
        }
    }
    return fail_counter;
}

int test_adder2()
{
    int fail_counter = 0;
    for (int I0 = 0; I0 < 4; I0++) {
        for (int I1 = 0; I1 < 4; I1++) {
            for (int carry = 0; carry < 2; carry++) {
                bits2_t bI0 = { .bits = {(I0 >> 0) & 1, (I0 >> 1) & 1} };
                bits2_t bI1 = { .bits = {(I1 >> 0) & 1, (I1 >> 1) & 1} };
                adder2_result_t result = adder2(bI0, bI1, carry);
                int expected_sum = (I0 + I1 + carry) & 3;
                int expected_carry = (I0 + I1 + carry) >> 2;
                ASSERT_EQ_BIT(expected_sum & 1, result.sum.bits[0]);
                ASSERT_EQ_BIT((expected_sum >> 1) & 1, result.sum.bits[1]);
                ASSERT_EQ_BIT(expected_carry, result.carry);
            }
        }
    }
    return fail_counter;
}

int test_adder4()
{
    int fail_counter = 0;
    for (int I0 = 0; I0 < 16; I0++) {
        for (int I1 = 0; I1 < 16; I1++) {
            for (int carry = 0; carry < 2; carry++) {
                bits4_t bI0 = { .bits = {(I0 >> 0) & 1, (I0 >> 1) & 1, (I0 >> 2) & 1, (I0 >> 3) & 1} };
                bits4_t bI1 = { .bits = {(I1 >> 0) & 1, (I1 >> 1) & 1, (I1 >> 2) & 1, (I1 >> 3) & 1} };
                adder4_result_t result = adder4(bI0, bI1, carry);
                int expected_sum = (I0 + I1 + carry) & 15;
                int expected_carry = (I0 + I1 + carry) >> 4;
                for (int bit = 0; bit < 4; bit++) {
                    ASSERT_EQ_BIT((expected_sum >> bit) & 1, result.sum.bits[bit]);
                }
                ASSERT_EQ_BIT(expected_carry, result.carry);
            }
        }
    }
    return fail_counter;
}

int test_adder8()
{
    int fail_counter = 0;
    for (int I0 = 0; I0 < 256; I0++) {
        for (int I1 = 0; I1 < 256; I1++) {
            for (int carry = 0; carry < 2; carry++) {
                byte_t bI0 = { .bits = {
                    (I0 >> 0) & 1, (I0 >> 1) & 1, (I0 >> 2) & 1, (I0 >> 3) & 1,
                    (I0 >> 4) & 1, (I0 >> 5) & 1, (I0 >> 6) & 1, (I0 >> 7) & 1
                }};
                byte_t bI1 = { .bits = {
                    (I1 >> 0) & 1, (I1 >> 1) & 1, (I1 >> 2) & 1, (I1 >> 3) & 1,
                    (I1 >> 4) & 1, (I1 >> 5) & 1, (I1 >> 6) & 1, (I1 >> 7) & 1
                }};
                adder8_result_t result = adder8(bI0, bI1, carry);
                int expected_sum = (I0 + I1 + carry) & 255;
                int expected_carry = (I0 + I1 + carry) >> 8;
                for (int bit = 0; bit < 8; bit++) {
                    ASSERT_EQ_BIT((expected_sum >> bit) & 1, result.sum.bits[bit]);
                }
                ASSERT_EQ_BIT(expected_carry, result.carry);
            }
        }
    }
    return fail_counter;
}

int test_adder32()
{
    int fail_counter = 0;
    uint32_t values[] = {0u, 1u, 0x12345678u, 0xFFFFFFFFu, 0x80000000u};

    for (int i0 = 0; i0 < 5; i0++) {
        for (int i1 = 0; i1 < 5; i1++) {
            for (int carry = 0; carry < 2; carry++) {
                uint64_t expected = (uint64_t)values[i0] + values[i1] + (uint32_t)carry;
                adder32_result_t result = adder32(word_from_uint32(values[i0]), word_from_uint32(values[i1]), carry);
                for (int bit = 0; bit < 32; bit++) {
                    ASSERT_EQ_BIT((expected >> bit) & 1u, result.sum.bits[bit]);
                }
                ASSERT_EQ_BIT(expected >> 32, result.carry);
            }
        }
    }

    if (fail_counter > 0) printf("test_adder32: %d tests failed\n", fail_counter);
    return fail_counter;
}

static int check_add_sub32(uint32_t i0, uint32_t i1, bit_t subtract)
{
    int fail_counter = 0;
    uint32_t expected = subtract ? i0 - i1 : i0 + i1;
    bit_t expected_carry = subtract ? i0 >= i1 : ((uint64_t)i0 + i1) >> 32;
    adder32_result_t result = add_sub32(word_from_uint32(i0), word_from_uint32(i1), subtract);

    for (int bit = 0; bit < 32; bit++) {
        ASSERT_EQ_BIT((expected >> bit) & 1u, result.sum.bits[bit]);
    }
    ASSERT_EQ_BIT(expected_carry, result.carry);
    return fail_counter;
}

int test_add_sub32()
{
    int fail_counter = 0;
    uint32_t values[] = {
        0u, 1u, 2u, 0xFFu, 0x100u, 0xFFFFu, 0x10000u,
        0xFFFFFFu, 0x1000000u, 0x7FFFFFFFu, 0x80000000u,
        0xFFFFFFFFu, 0xAAAAAAAAu, 0x55555555u, 0x12345678u
    };

    for (size_t i0 = 0; i0 < sizeof(values) / sizeof(values[0]); i0++) {
        for (size_t i1 = 0; i1 < sizeof(values) / sizeof(values[0]); i1++) {
            for (int subtract = 0; subtract < 2; subtract++) {
                fail_counter += check_add_sub32(values[i0], values[i1], subtract);
            }
        }
    }

    for (int bit = 0; bit < 32; bit++) {
        uint32_t boundary = UINT32_C(1) << bit;
        fail_counter += check_add_sub32(boundary - 1u, 1u, 0);
        fail_counter += check_add_sub32(boundary, 1u, 1);
        fail_counter += check_add_sub32(0u, boundary, 1);
        fail_counter += check_add_sub32(boundary, boundary, 1);
    }

    if (fail_counter > 0) printf("test_add_sub32: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_adder()
{
    int fail_counter = 0;
    fail_counter += test_half_adder();
    fail_counter += test_adder1();
    fail_counter += test_adder2();
    fail_counter += test_adder4();
    fail_counter += test_adder8();
    fail_counter += test_adder32();
    fail_counter += test_add_sub32();
    printf("total adder tests failed: %d\n", fail_counter);
    return fail_counter;
}
