#include "test.h"

int test_nand_gate()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, nand_gate(0, 0));
    ASSERT_EQ_BIT(1, nand_gate(0, 1));
    ASSERT_EQ_BIT(1, nand_gate(1, 0));
    ASSERT_EQ_BIT(0, nand_gate(1, 1));
    if (fail_counter > 0) printf("test_nand: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_not_gate()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, not_gate(0));
    ASSERT_EQ_BIT(0, not_gate(1));
    if (fail_counter > 0) printf("test_not: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_and_gate()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(0, and_gate(0, 0));
    ASSERT_EQ_BIT(0, and_gate(0, 1));
    ASSERT_EQ_BIT(0, and_gate(1, 0));
    ASSERT_EQ_BIT(1, and_gate(1, 1));
    if (fail_counter > 0) printf("test_and: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_and_gate3()
{
    int fail_counter = 0;
    for (int inputs = 0; inputs < 8; inputs++) {
        bit_t i0 = (inputs >> 0) & 1;
        bit_t i1 = (inputs >> 1) & 1;
        bit_t i2 = (inputs >> 2) & 1;
        ASSERT_EQ_BIT(i0 && i1 && i2, and_gate3(i0, i1, i2));
    }
    if (fail_counter > 0) printf("test_and_gate3: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_and_gate4()
{
    int fail_counter = 0;
    for (int inputs = 0; inputs < 16; inputs++) {
        bit_t i0 = (inputs >> 0) & 1;
        bit_t i1 = (inputs >> 1) & 1;
        bit_t i2 = (inputs >> 2) & 1;
        bit_t i3 = (inputs >> 3) & 1;
        ASSERT_EQ_BIT(i0 && i1 && i2 && i3, and_gate4(i0, i1, i2, i3));
    }
    if (fail_counter > 0) printf("test_and_gate4: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_and_gate8()
{
    int fail_counter = 0;
    for (int inputs = 0; inputs < 256; inputs++) {
        bit_t i0 = (inputs >> 0) & 1;
        bit_t i1 = (inputs >> 1) & 1;
        bit_t i2 = (inputs >> 2) & 1;
        bit_t i3 = (inputs >> 3) & 1;
        bit_t i4 = (inputs >> 4) & 1;
        bit_t i5 = (inputs >> 5) & 1;
        bit_t i6 = (inputs >> 6) & 1;
        bit_t i7 = (inputs >> 7) & 1;
        ASSERT_EQ_BIT(
            i0 && i1 && i2 && i3 && i4 && i5 && i6 && i7,
            and_gate8(i0, i1, i2, i3, i4, i5, i6, i7)
        );
    }
    if (fail_counter > 0) printf("test_and_gate8: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_or_gate()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(0, or_gate(0, 0));
    ASSERT_EQ_BIT(1, or_gate(0, 1));
    ASSERT_EQ_BIT(1, or_gate(1, 0));
    ASSERT_EQ_BIT(1, or_gate(1, 1));
    if (fail_counter > 0) printf("test_or: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_xor_gate()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(0, xor_gate(0, 0));
    ASSERT_EQ_BIT(1, xor_gate(0, 1));
    ASSERT_EQ_BIT(1, xor_gate(1, 0));
    ASSERT_EQ_BIT(0, xor_gate(1, 1));
    if (fail_counter > 0) printf("test_xor: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_nor_gate()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, nor_gate(0, 0));
    ASSERT_EQ_BIT(0, nor_gate(0, 1));
    ASSERT_EQ_BIT(0, nor_gate(1, 0));
    ASSERT_EQ_BIT(0, nor_gate(1, 1));
    if (fail_counter > 0) printf("test_nor: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_xnor_gate()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, xnor_gate(0, 0));
    ASSERT_EQ_BIT(0, xnor_gate(0, 1));
    ASSERT_EQ_BIT(0, xnor_gate(1, 0));
    ASSERT_EQ_BIT(1, xnor_gate(1, 1));
    if (fail_counter > 0) printf("test_xnor: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_gates()
{
    int gates_fail_counter = 0;
    gates_fail_counter += test_nand_gate();
    gates_fail_counter += test_not_gate();
    gates_fail_counter += test_and_gate();
    gates_fail_counter += test_and_gate3();
    gates_fail_counter += test_and_gate4();
    gates_fail_counter += test_and_gate8();
    gates_fail_counter += test_or_gate();
    gates_fail_counter += test_xor_gate();
    gates_fail_counter += test_nor_gate();
    gates_fail_counter += test_xnor_gate();
    printf("Total gates tests failed: %d\n", gates_fail_counter);
    return gates_fail_counter;
}
