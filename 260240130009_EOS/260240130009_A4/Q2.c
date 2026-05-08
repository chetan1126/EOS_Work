//PRN : 260240130009



#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For getpid()

#define NUM_THREADS 5

void* thread_work(void* arg) 
{
	// Casting the void pointer back to an integer
	int thread_num = *((int*)arg);

	// getpid() returns the Process ID
	printf("Thread %d: Process ID = %d\n", thread_num, getpid());

	return NULL;
}

int main() 
{
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; i++) 
	{
		thread_ids[i] = i + 1; // Assigning a unique ID

		printf("Main: Creating thread %d\n", thread_ids[i]);

		if(pthread_create(&threads[i], NULL, thread_work, (void*)&thread_ids[i]) != 0) 
		{
	    		perror("Failed to create thread");
	    		return 1;
		}
	}

	// Main thread must join all threads to ensure they finish
	for (int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_join(threads[i], NULL);
	}

	printf("Main: All threads completed.\n");
	return 0;
}
