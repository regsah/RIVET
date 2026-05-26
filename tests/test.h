#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define ASSERT_EQ_BIT(expected, actual)                                 \
    do {                                                                \
        if ((expected) != (actual)) {                                   \
            printf("Assertion failed at %s:%d: expected %u, got %u\n",  \
                __FILE__, __LINE__,                                     \
                (unsigned)(expected), (unsigned)(actual)                \
            );                                                          \
            return -1;                                                  \
        }                                                               \
    } while (0)
        
#endif // TEST_H