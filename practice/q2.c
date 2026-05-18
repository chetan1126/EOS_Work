/* 
Question 2

Write a Linux C program where:

Parent creates shared memory and semaphore
Parent forks two child processes
Child processes write process information into shared memory
Use semaphore to avoid race condition
Parent displays all stored data
Handle SIGINT to clean shared memory and semaphore properly 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>


int semaphore_id, shm_id;
typedef struct
{
char msg1[100];
char msg2[100];
}data;

data *shm_ptr;
sem_t sem;



int main()
{
	shm_id = shmget(IPC_PRIVATE, sizeof(data), 0666 | IPC_CREAT);
	
	if(shm_id <0)
	{
		printf(" share memory fail\n");
		return 1;
	}
	
	if(sem_init(&sem,0,1) != 0)
	{
		printf("error\n");
		return 0;
	}
	shm_ptr =shmat(shm_id, NULL, 0);
	
	pid_t pid1 = fork();
	if(pid1 == 0)
	{
		//sem_wait(&sem);
		sprintf(shm_ptr->msg1, "chiled1 pid= %d,parent pid = %d", getpid(),getppid());
		printf(" child 1 in child =%s\n", shm_ptr->msg1);
		//strcpy(shm_ptr, msg1);
		printf("child1 write\n");
		//sem_post(&sem);
		return 2;
	}
	
	shm_ptr =shmat(shm_id, NULL, 0);
	
	//strcpy(msg2, shm_ptr);
	pid_t pid2 = fork();	
	if(pid2 == 0)
	{
		//sem_wait(&sem);
		sprintf(shm_ptr->msg2, "chiled2 pid= %d,parent pid = %d", getpid(),getppid());
		printf(" child 2 in child =%s\n", shm_ptr->msg2);
		//strcpy(shm_ptr, msg2);
		printf("child2 write\n");
		//sem_post(&sem);
		return 3;
	}
	
	wait(NULL);
	wait(NULL);
	printf(" child 1 =%s\n", shm_ptr->msg1);
	printf(" child 2 =%s\n", shm_ptr->msg2);
	
	//cleanup(0);
	    shmdt(shm_ptr);

    shmctl(shm_id, IPC_RMID, NULL);
	sem_destroy(&sem);
	return 0;
	


}
