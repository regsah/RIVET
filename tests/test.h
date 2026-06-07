#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#include "gates.h"
#include "combinational.h"
#include "latch.h"

int test_gates();
int test_mux();
int test_dmux();
int test_adder();
int test_decoder();
int test_comparators();
int test_latch();

#define ASSERT_EQ_BIT(expected, actual)                                 \
    do {                                                                \
        if ((expected) != (actual)) {                                   \
            printf("Assertion failed at %s:%d: expected %u, got %u\n",  \
                __FILE__, __LINE__,                                     \
                (unsigned)(expected), (unsigned)(actual)                \
            );                                                          \
            fail_counter++;                                             \
        }                                                               \
    } while (0)
        
#endif // TEST_H
