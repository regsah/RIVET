#include "test.h"

int main()
{
    int total_failures = 0;
    total_failures += test_gates();
    total_failures += test_mux();
    total_failures += test_dmux();
    total_failures += test_adder();
    total_failures += test_decoder();
    total_failures += test_comparators();
    total_failures += test_latch();
    total_failures += test_flip_flop();
    total_failures += test_register();
    printf("Total failures: %d\n", total_failures);
    return total_failures;
}
