#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>

void* char_count(void *arg);
int pipefd[2];
#define size 1024

int total_chars = 0;
pthread_mutex_t lock;

int main(){
	int child1, child2;
	//int pipefd[2];
	pthread_t thread; // initilized thread
	
       	
	if(pipe(pipefd) == -1){
	perror("pipe");
	return 1;
	// pipe fail
	}
	
	printf("pipe created\n");
	// 0 -- read
	// 1-- write
	sleep(1);
	
	if(pthread_create(&thread, NULL, char_count,NULL) != 0)
	{
		printf("thread creat\n");
		return 2;
	}
	
	child1 = fork(); // for child 1

	if(child1 == 0)
	{
		printf("child1\n");

		close(pipefd[0]); // read close
		dup2(pipefd[1], 1);
                close(pipefd[1]); // write close

		printf("child1\n");
		execlp("ls", "ls",NULL);
		
		perror("execlp ls");
        	exit(EXIT_FAILURE);
		return 0;
	}
	child2 = fork();

	if(child2 == 0)
	{
		printf("child2\n");

		close(pipefd[0]); // read close
                dup2(pipefd[1], 1);
                close(pipefd[1]); // write close

        	printf("child2\n");
        	execlp("pwd", "pwd",NULL);

		perror("execlp pwd");
        	exit(EXIT_FAILURE);
	return 0;
        }

	close(pipefd[1]); // close of parent write

	wait(NULL);
	wait(NULL);

	pthread_join(thread,NULL);

	printf("taoat = %d\n", total_chars);

	return 0;


}

void* char_count(void *arg)
{
	printf("function\n");
	
	char buffer[size];
	int n ;
	while(( n = read(pipefd[0] , buffer, sizeof(buffer))) > 0)
	{
		pthread_mutex_lock(&lock);
		total_chars += n;
		write(1, buffer, n);
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}
