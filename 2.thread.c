#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// This data is shared by the thread (s)
int sum; 
void *runner(void *param);

int main(int argc, char *argv[])
{
  // The thread identifier
  pthread_t tid; 
  // Set of thread attributes
  pthread_attr_t attr;
  
  if (argc != 2) {
    fprintf(stderr, "usage: a.out <integer value>\n");
    return -1;
  }

  if (atoi(argv[1]) < 0) {
    fprintf(stderr, "%d must be >= 0", atoi(argv[1]));
    return -1;
  }

  // Get default attribute
  pthread_attr_init(&attr);
  // Create the thread
  pthread_create(&tid, &attr, runner, argv[1]);
  // Wait for the thread to exit
  pthread_join(tid, NULL);
  printf("sum = %d\n", sum);
}

void *runner(void *param) {
  int i, upper = atoi(param);
  sum = 0;

  for (i = 1; i <= upper; i++) {
    sum += i;
  }

  pthread_exit(0);
}