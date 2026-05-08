//PRN : 260240130009



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // Current number of items in buffer

pthread_mutex_t mutex;
pthread_cond_t cond_full;  // Signaled when buffer has space
pthread_cond_t cond_empty; // Signaled when buffer has data

void* producer(void* arg) 
{
	for (int i = 0; i < 10; i++) 
	{
		pthread_mutex_lock(&mutex);

	        // While buffer is full, wait for space
		while (count == BUFFER_SIZE) 
		{
			printf("Buffer full. Producer waiting...\n");
		        pthread_cond_wait(&cond_full, &mutex);
		}

		// Add item to buffer
		buffer[count] = i;
		printf("Producer: Produced %d (Items in buffer: %d)\n", i, count + 1);
		count++;

		// Signal consumer that there is data available
		pthread_cond_signal(&cond_empty);

		pthread_mutex_unlock(&mutex);
		sleep(1); // Simulate work
	}
	return NULL;
}

void* consumer(void* arg) 
{
	for (int i = 0; i < 10; i++) 
	{
		pthread_mutex_lock(&mutex);

		// While buffer is empty, wait for data
		while (count == 0) 
		{
		    printf("Buffer empty. Consumer waiting...\n");
		    pthread_cond_wait(&cond_empty, &mutex);
		}

		// Remove item from buffer
		int item = buffer[count - 1];
		count--;
		printf("Consumer: Consumed %d (Items in buffer: %d)\n", item, count);

		// Signal producer that there is space available
		pthread_cond_signal(&cond_full);

		pthread_mutex_unlock(&mutex);
		usleep(150000); // Consumer is faster/slower than producer
	}
	return NULL;
}

int main() 
{
	pthread_t prod_tid, cons_tid;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_full, NULL);
	pthread_cond_init(&cond_empty, NULL);

	pthread_create(&prod_tid, NULL, producer, NULL);
	pthread_create(&cons_tid, NULL, consumer, NULL);

	pthread_join(prod_tid, NULL);
	pthread_join(cons_tid, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_full);
	pthread_cond_destroy(&cond_empty);

	return 0;
}
