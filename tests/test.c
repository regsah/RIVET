#include "test.h"

int main()
{
    int total_failures = 0;
    total_failures += test_gates();
    total_failures += test_mux();
    printf("Total failures: %d\n", total_failures);
    return total_failures;
}