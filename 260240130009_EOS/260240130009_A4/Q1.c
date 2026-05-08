//PRN : 260240130009


#include <stdio.h>
#include <pthread.h>

// This is the function the thread will run
void* thread_function(void* arg) 
{
	printf("Hello from thread\n");
	return NULL;
}


int main() 
{
	pthread_t my_thread;

	// Creation of the thread.
	// Parameters: (thread id, attributes, function to run, arguments)
	if (pthread_create(&my_thread, NULL, thread_function, NULL) != 0)
	{
		perror("Failed to create thread");
		return 1;
	}

	// Print from the main thread
	printf("Hello from main\n");

	// Wait for the thread to finish
	pthread_join(my_thread, NULL);

	return 0;
}
