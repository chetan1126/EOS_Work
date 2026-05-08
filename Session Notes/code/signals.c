#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void graceful(int signum) {
  printf("\tChild process received signal: %i\n", signum);
  puts("\tChild process terminating gracefully ...");
  sleep(1);
  puts("\tChild process terminating now...");
  _exit(0); /* fast-track notification of parent */
}
void set_handler() {
  struct sigaction current;
  sigemptyset(&current.sa_mask);         /* clear the signal set */
  current.sa_flags = 0;                  /* enables setting sa_handler, not sa_action */
  current.sa_handler = graceful;         /* specify a handler */
  sigaction(SIGTERM, &current, NULL);    /* register the handler */
}
void child_code() {
  set_handler();
  while (1) {   /** loop until interrupted **/
    puts("\tChild sleeping for 1 sec.");
    sleep(1);
    puts("\tChild wakes up.");
  }
}
void parent_code(pid_t cpid) {
  puts("Parent sleeping for 5 sec...");
  sleep(5);
  /* Try to terminate child. */
  if (kill(cpid, SIGTERM) == -1) {
    perror("kill");
    exit(-1);
  }
  wait(NULL); /** wait for child to terminate **/
  puts("Child process terminated, Parent exiting...");
}
int main() {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return -1; /* error */
  }
  if (pid == 0)
    child_code();
  else
    parent_code(pid);
  return 0;  /* normal */
}
