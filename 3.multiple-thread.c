#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREAD 5

void *PrintHello(void *threadid)
{
  long tid;
  tid = (long) threadid;
  printf("Hello World! It's me, thread #%ld!\n", tid);

  pthread_exit(0);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREAD];
  int rc;
  long t;
  
  for(t = 0; t < NUM_THREAD; t++) 
  {
    printf("In main: creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *) t);

    if (rc) 
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  pthread_exit(NULL);
}