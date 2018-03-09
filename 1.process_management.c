#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

  pid_t pid;
  int x = 10;

  // fork another process 
  // form from System Call
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
    x = x + 2;
    printf("x = %d\n", x);
    printf("x again = %d\n", x);
  }
  else 
  {
    // Parent Process
    wait(NULL);
    printf("Child Complete x = %d\n", x);
    exit(0);
  }

  return 0;
}
