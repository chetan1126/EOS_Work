//PRN : 260240130009

#include <stdio.h>

int main() {
    printf("Safe Real-Time Task Started...\n");
    
    double result = 1.0;
    // This loop count is high enough to take ~5-10 seconds 
    // depending on your CPU speed.
    for (long i = 0; i < 2000000000; i++) {
        result *= 1.00000001;
    }

    printf("Safe Real-Time Task Finished. Result: %f\n", result);
    return 0;
}
