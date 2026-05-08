//PRN : 260240130009



#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS 1000

// Global variables
int counter = 0;
pthread_mutex_t lock; // The mutex lock

void* increment_counter(void* arg) 
{
	for (int i = 0; i < INCREMENTS; i++) 
	{
		// Lock the mutex before entering the critical section
		pthread_mutex_lock(&lock);

		counter++; // Critical Section

		// Unlock the mutex so other threads can enter
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main() 
{
	pthread_t threads[NUM_THREADS];

	// Initialize the mutex
	if(pthread_mutex_init(&lock, NULL) != 0) 
	{
		printf("Mutex init failed\n");
		return 1;
	}

	// Create 4 threads
	for (int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_create(&threads[i], NULL, increment_counter, NULL);
	}

	// Wait for all threads to finish
	for (int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_join(threads[i], NULL);
	}

	printf("Final counter value: %d\n", counter);
	printf("Expected value: %d\n", NUM_THREADS * INCREMENTS);

	// Destroy the mutex
	pthread_mutex_destroy(&lock);

	return 0;
}
