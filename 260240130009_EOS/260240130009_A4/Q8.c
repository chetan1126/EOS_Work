//PRN : 260240130009



#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS 100000 // Higher number makes the race condition obvious without a mutex

int counter = 0;
pthread_mutex_t lock; // Declare the mutex

void* increment_task(void* arg) 
{
	for(int i = 0; i < INCREMENTS; i++) 
	{
		// Acquire the lock
		pthread_mutex_lock(&lock);

		counter++; 

		// Release the lock
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main() 
{
	pthread_t threads[NUM_THREADS];

	// Initialize the mutex before creating threads
	if (pthread_mutex_init(&lock, NULL) != 0) 
	{
		printf("Mutex initialization failed\n");
		return 1;
	}

	// Create 4 threads
	for (int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_create(&threads[i], NULL, increment_task, NULL);
	}

	// Wait for all threads
	for (int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_join(threads[i], NULL);
	}

	printf("Final Counter: %d\n", counter);
	printf("Expected Counter: %d\n", NUM_THREADS * INCREMENTS);

	// Clean up the mutex
	pthread_mutex_destroy(&lock);

	return 0;
}
