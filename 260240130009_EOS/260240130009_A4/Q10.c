//PRN : 260240130009



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 3
#define MAX_TASKS 10

// Task structure representing a simple computation
typedef struct 
{
	int id;
	int data;
} Task;

// Task Queue
Task task_queue[MAX_TASKS];
int task_count = 0;

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;

// Worker function
void* worker_thread(void* arg) 
{
	int thread_id = *(int*)arg;
	free(arg);

	while (1) 
	{
		Task task;

		pthread_mutex_lock(&queue_mutex);

		// Wait until there is a task in the queue
		while (task_count == 0) 
		{
	    		pthread_cond_wait(&queue_cond, &queue_mutex);
		}

		// Pull task from queue (First In, First Out)
		task = task_queue[0];
		for (int i = 0; i < task_count - 1; i++) 
		{
	    		task_queue[i] = task_queue[i + 1];
		}
		task_count--;

		pthread_mutex_unlock(&queue_mutex);

		// Execute the task
		printf("Worker %d: Executing Task ID %d (Squaring %d -> %d)\n", thread_id, task.id, task.data, task.data * task.data);

		usleep(500000); // Simulate processing time
	}
	return NULL;
}

void submit_task(Task t) 
{
	pthread_mutex_lock(&queue_mutex);
	if (task_count < MAX_TASKS) 
	{
		task_queue[task_count++] = t;
		pthread_cond_signal(&queue_cond); // Wake up one worker
	}
	pthread_mutex_unlock(&queue_mutex);
}

int main() 
{
	pthread_t pool[THREAD_POOL_SIZE];
	pthread_mutex_init(&queue_mutex, NULL);
	pthread_cond_init(&queue_cond, NULL);

	// Create fixed number of worker threads
	for (int i = 0; i < THREAD_POOL_SIZE; i++) 
	{
		int* id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&pool[i], NULL, worker_thread, id);
	}

	// Dynamically assign tasks
	for (int i = 0; i < 8; i++) 
	{
		Task t = { .id = i + 1, .data = i + 5 };
		printf("Main: Submitting Task %d\n", t.id);
		submit_task(t);
		usleep(100000); // Main thread submits tasks over time
	}

	// In a real application, you'd implement a shutdown flag
	// For this simulation, we'll let it run for a bit then exit
	sleep(5);
	printf("Main: All tasks processed. Simulation ending.\n");

	return 0;
}
