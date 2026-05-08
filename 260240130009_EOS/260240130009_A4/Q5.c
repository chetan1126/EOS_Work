//PRN : 260240130009



#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Function to calculate factorial
void* compute_factorial(void* arg) 
{
	int n = *(int*)arg;
	long long *result = malloc(sizeof(long long)); // Allocate memory for result
	*result = 1;

	for(int i = 1; i <= n; i++) 
	{
		*result *= i;
	}

	printf("Thread: Calculated %d! = %lld\n", n, *result);

	// Exit and return the pointer to the result
	pthread_exit((void*)result);
}

int main() 
{
	int num_threads = 3;
	pthread_t threads[num_threads];
	int inputs[] = {5, 10, 12}; // Numbers to calculate factorial for
	void* return_value;         // Pointer to catch the result

	for(int i = 0; i < num_threads; i++) 
	{
		pthread_create(&threads[i], NULL, compute_factorial, &inputs[i]);
	}

	for (int i = 0; i < num_threads; i++) 
	{
		// Collect the result from the thread
		pthread_join(threads[i], &return_value);

		long long *res_ptr = (long long*)return_value;
		printf("Main: Thread %d returned %lld\n", i + 1, *res_ptr);

		// Free the memory allocated inside the thread
		free(res_ptr);
	}

	printf("Main: All results collected.\n");
	return 0;
}
