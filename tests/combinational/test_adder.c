#include "test.h"
#include "combinational.h"

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

int test_adder()
{
    int fail_counter = 0;
    fail_counter += test_half_adder();
    fail_counter += test_adder1();
    fail_counter += test_adder2();
    fail_counter += test_adder4();
    fail_counter += test_adder8();
    printf("total adder tests failed: %d\n", fail_counter);
    return fail_counter;
}