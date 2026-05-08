//PRN : 260240130009


#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Required for sleep()

void* thread_task(void* arg) 
{
	int id = *(int*)arg;
	int sleep_time = id * 2; // Each thread sleeps for a different duration

	printf("Thread %d: Starting (Will sleep for %d seconds)...\n", id, sleep_time);

	sleep(sleep_time); // Simulating work

	printf("Thread %d: Finished work.\n", id);
	return NULL;
}

int main() 
{
	pthread_t threads[3];
	int thread_args[3];

	// Creating 3 threads
	for (int i = 0; i < 3; i++) 
	{
		thread_args[i] = i + 1;
		printf("Main: Creating thread %d\n", thread_args[i]);
		pthread_create(&threads[i], NULL, thread_task, &thread_args[i]);
	}

	// Main thread enters the 'join' phase
	for (int i = 0; i < 3; i++) 
	{
		printf("Main: Waiting for thread %d to finish...\n", i + 1);
		pthread_join(threads[i], NULL);
		printf("Main: Thread %d has joined.\n", i + 1);
	}

	printf("Main: All threads are done. Exiting program.\n");
	return 0;
}
