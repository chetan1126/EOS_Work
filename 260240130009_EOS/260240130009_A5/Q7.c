//PRN : 260240130009

#include <stdio.h>

int main() {
    double result = 1.0;
    // Perform a large number of multiplications
    for (long i = 1; i < 100000000; i++) {
        result *= 1.00000001;
    }
    printf("Final result: %f\n", result);
    return 0;
}
