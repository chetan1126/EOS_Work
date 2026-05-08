//PRN : 260240130009

// loop.c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Process started with PID: %d\n", getpid());
    printf("Running infinite loop... Press Ctrl+C to stop (if possible).\n");
    
    while(1) {
        // Simple work to keep the CPU busy
    }
    return 0;
}
