//PRN : 260240130009

#include <stdio.h>

int main() {
    double result = 1.0;
    // A long loop to keep the CPU busy for a few seconds
    for (long i = 0; i < 500000000; i++) {
        result *= 1.00000001;
    }
    // Print something at the end so we know it finished
    printf("Task Finished. Result: %f\n", result);
    return 0;
}
