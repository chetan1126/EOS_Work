//PRN : 260240130009



#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep()

void* infinite_loop_task(void* arg) 
{
	printf("Thread: Entering infinite loop...\n");

	while (1) 
	{
		printf("Thread: I am still running...\n");
		sleep(1); 

		// pthread_testcancel() creates a cancellation point
		// sleep() is also a cancellation point
		pthread_testcancel();
	}

	return NULL;
}

int main() 
{
	pthread_t my_thread;

	// Start the thread
	if(pthread_create(&my_thread, NULL, infinite_loop_task, NULL) != 0) 
	{
		perror("pthread_create");
		return 1;
	}

	// Let the thread run for a few seconds
	sleep(3);

	// Cancel the thread
	printf("Main: Sending cancellation request to thread...\n");
	pthread_cancel(my_thread);

	// Join the thread to clean up resources
	// The exit status of a cancelled thread is PTHREAD_CANCELED
	void* status;
	pthread_join(my_thread, &status);

	if (status == PTHREAD_CANCELED) 
	{
		printf("Main: Thread was successfully cancelled.\n");
	} 
	else 
	{
		printf("Main: Thread exited normally.\n");
	}

	return 0;
}
