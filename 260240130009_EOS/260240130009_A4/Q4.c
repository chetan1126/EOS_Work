//PRN : 260240130009



#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4

// Function executed by each thread
void* calculate_square(void* arg) 
{
	// Cast the void pointer back to an int pointer, then dereference
	int val = *(int*)arg;
	int square = val * val;

	printf("Thread: Input = %d, Square = %d\n", val, square);

	return NULL;
}

int main() 
{
	pthread_t threads[NUM_THREADS];
	int numbers[NUM_THREADS]; // Dedicated memory for each thread's argument

	// Create threads
	for(int i = 0; i < NUM_THREADS; i++) 
	{
		numbers[i] = i + 2; // Passing numbers: 2, 3, 4, 5

		if(pthread_create(&threads[i], NULL, calculate_square, &numbers[i]) != 0) 
		{
		    perror("pthread_create failed");
		    return 1;
		}
	}

	// Join threads
	for(int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_join(threads[i], NULL);
	}

	printf("Main: All squares calculated successfully.\n");
	return 0;
}
