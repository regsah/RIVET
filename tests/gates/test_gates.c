#include "gates.h"
#include "test.h"

int test_nand()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, nand_gate(0, 0));
    ASSERT_EQ_BIT(1, nand_gate(0, 1));
    ASSERT_EQ_BIT(1, nand_gate(1, 0));
    ASSERT_EQ_BIT(0, nand_gate(1, 1));
    printf("test_nand: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_not()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, not_gate(0));
    ASSERT_EQ_BIT(0, not_gate(1));
    printf("test_not: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_and()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(0, and_gate(0, 0));
    ASSERT_EQ_BIT(0, and_gate(0, 1));
    ASSERT_EQ_BIT(0, and_gate(1, 0));
    ASSERT_EQ_BIT(1, and_gate(1, 1));
    printf("test_and: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_or()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(0, or_gate(0, 0));
    ASSERT_EQ_BIT(1, or_gate(0, 1));
    ASSERT_EQ_BIT(1, or_gate(1, 0));
    ASSERT_EQ_BIT(1, or_gate(1, 1));
    printf("test_or: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_xor()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(0, xor_gate(0, 0));
    ASSERT_EQ_BIT(1, xor_gate(0, 1));
    ASSERT_EQ_BIT(1, xor_gate(1, 0));
    ASSERT_EQ_BIT(0, xor_gate(1, 1));
    printf("test_xor: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_nor()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, nor_gate(0, 0));
    ASSERT_EQ_BIT(0, nor_gate(0, 1));
    ASSERT_EQ_BIT(0, nor_gate(1, 0));
    ASSERT_EQ_BIT(0, nor_gate(1, 1));
    printf("test_nor: %d tests failed\n", fail_counter);
    return fail_counter;
}

int test_xnor()
{
    int fail_counter = 0;
    ASSERT_EQ_BIT(1, xnor_gate(0, 0));
    ASSERT_EQ_BIT(0, xnor_gate(0, 1));
    ASSERT_EQ_BIT(0, xnor_gate(1, 0));
    ASSERT_EQ_BIT(1, xnor_gate(1, 1));
    printf("test_xnor: %d tests failed\n", fail_counter);
    return fail_counter;
}

int main()
{
    int total_fail_counter = 0;
    total_fail_counter += test_nand();
    total_fail_counter += test_not();
    total_fail_counter += test_and();
    total_fail_counter += test_or();
    total_fail_counter += test_xor();
    total_fail_counter += test_nor();
    total_fail_counter += test_xnor();
    printf("Total gates tests failed: %d out of %d\n", total_fail_counter, 26);
    return total_fail_counter;
}