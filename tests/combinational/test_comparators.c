#include "test.h"

int test_eq1()
{
    int fail_counter = 0;
    for (int i0 = 0; i0 < 2; i0++) {
        for (int i1 = 0; i1 < 2; i1++) {
            ASSERT_EQ_BIT(i0 == i1, eq1(i0, i1));
        }
    }
    if (fail_counter > 0) printf("test_eq1: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_eq2()
{
    int fail_counter = 0;
    for (int I0 = 0; I0 < 4; I0++) {
        for (int I1 = 0; I1 < 4; I1++) {
            bits2_t bI0 = { .bits = {(I0 >> 0) & 1, (I0 >> 1) & 1} };
            bits2_t bI1 = { .bits = {(I1 >> 0) & 1, (I1 >> 1) & 1} };
            ASSERT_EQ_BIT(I0 == I1, eq2(bI0, bI1));
        }
    }
    if (fail_counter > 0) printf("test_eq2: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_eq4()
{
    int fail_counter = 0;
    for (int I0 = 0; I0 < 16; I0++) {
        for (int I1 = 0; I1 < 16; I1++) {
            bits4_t bI0 = { .bits = {
                (I0 >> 0) & 1,
                (I0 >> 1) & 1,
                (I0 >> 2) & 1,
                (I0 >> 3) & 1
            } };
            bits4_t bI1 = { .bits = {
                (I1 >> 0) & 1,
                (I1 >> 1) & 1,
                (I1 >> 2) & 1,
                (I1 >> 3) & 1
            } };
            ASSERT_EQ_BIT(I0 == I1, eq4(bI0, bI1));
        }
    }
    if (fail_counter > 0) printf("test_eq4: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_eq8()
{
    int fail_counter = 0;
    for (int I0 = 0; I0 < 256; I0++) {
        for (int I1 = 0; I1 < 256; I1++) {
            byte_t bI0 = { .bits = {
                (I0 >> 0) & 1, (I0 >> 1) & 1, (I0 >> 2) & 1, (I0 >> 3) & 1,
                (I0 >> 4) & 1, (I0 >> 5) & 1, (I0 >> 6) & 1, (I0 >> 7) & 1
            } };
            byte_t bI1 = { .bits = {
                (I1 >> 0) & 1, (I1 >> 1) & 1, (I1 >> 2) & 1, (I1 >> 3) & 1,
                (I1 >> 4) & 1, (I1 >> 5) & 1, (I1 >> 6) & 1, (I1 >> 7) & 1
            } };
            ASSERT_EQ_BIT(I0 == I1, eq8(bI0, bI1));
        }
    }
    if (fail_counter > 0) printf("test_eq8: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_is_zero()
{
    int fail_counter = 0;
    for (int i = 0; i < 2; i++) {
        ASSERT_EQ_BIT(i == 0, is_zero(i));
    }
    if (fail_counter > 0) printf("test_is_zero: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_is_zero2()
{
    int fail_counter = 0;
    for (int I = 0; I < 4; I++) {
        bits2_t bI = { .bits = {(I >> 0) & 1, (I >> 1) & 1} };
        ASSERT_EQ_BIT(I == 0, is_zero2(bI));
    }
    if (fail_counter > 0) printf("test_is_zero2: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_is_zero4()
{
    int fail_counter = 0;
    for (int I = 0; I < 16; I++) {
        bits4_t bI = { .bits = {
            (I >> 0) & 1,
            (I >> 1) & 1,
            (I >> 2) & 1,
            (I >> 3) & 1
        } };
        ASSERT_EQ_BIT(I == 0, is_zero4(bI));
    }
    if (fail_counter > 0) printf("test_is_zero4: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_is_zero8()
{
    int fail_counter = 0;
    for (int I = 0; I < 256; I++) {
        byte_t bI = { .bits = {
            (I >> 0) & 1, (I >> 1) & 1, (I >> 2) & 1, (I >> 3) & 1,
            (I >> 4) & 1, (I >> 5) & 1, (I >> 6) & 1, (I >> 7) & 1
        } };
        ASSERT_EQ_BIT(I == 0, is_zero8(bI));
    }
    if (fail_counter > 0) printf("test_is_zero8: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_comparators()
{
    int fail_counter = 0;
    fail_counter += test_eq1();
    fail_counter += test_eq2();
    fail_counter += test_eq4();
    fail_counter += test_eq8();
    fail_counter += test_is_zero();
    fail_counter += test_is_zero2();
    fail_counter += test_is_zero4();
    fail_counter += test_is_zero8();
    printf("total comparator tests failed: %d\n", fail_counter);
    return fail_counter;
}
