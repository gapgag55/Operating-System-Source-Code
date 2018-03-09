#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>

#define TRUE 1

int main() {

  pid_t pid;

  // fork another process 
  pid = fork();

  // Error occurred
  if (pid < 0) 
  {
    fprintf(stderr, "Fork failed");
    exit(-1);
  } 
  // Child Process
  else if (pid == 0)
  {
    execlp("/bin/ls", "ls", NULL);
  }
  else 
  {
    // Parent Process
    wait(NULL);
    printf("Child Complete");
    exit(0);
  }

  return 0;
}