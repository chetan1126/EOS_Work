// parent_child_pipe_thread.c
/*
Write a Linux C program where:

Parent creates one pipe
Parent forks two child processes
Child-1 executes ls
Child-2 executes pwd
Both send output to parent using pipe
Parent creates one thread to count total characters received
Use mutex for synchronization
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int pipefd[2];

int total_chars = 0;
pthread_mutex_t lock;

// Thread function to count characters
void *count_characters(void *arg)
{
    char buffer[BUFFER_SIZE];
    int n;

    while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0)
    {
        pthread_mutex_lock(&lock);

        total_chars += n;

        // Display received data
        write(STDOUT_FILENO, buffer, n);

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main()
{
    pid_t child1, child2;
    pthread_t tid;

    // Create pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create thread in parent
    if (pthread_create(&tid, NULL, count_characters, NULL) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Fork Child-1
    child1 = fork();

    if (child1 == 0)
    {
        // Child-1 writes to pipe
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execlp("ls", "ls", NULL);

        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    // Fork Child-2
    child2 = fork();

    if (child2 == 0)
    {
        // Child-2 writes to pipe
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execlp("pwd", "pwd", NULL);

        perror("execlp pwd");
        exit(EXIT_FAILURE);
    }

    // Parent process NU
    close(pipefd[1]);

    // Wait for children
    wait(NULL);
    wait(NULL);

    // Wait for thread to finish
    pthread_join(tid, NULL);

    // Print total characters
    printf("\n\nTotal characters received = %d\n", total_chars);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
