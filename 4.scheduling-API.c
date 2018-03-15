#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
  long tid;
  tid = (long) threadid;
  printf("Hello World! It's me, thread #%ld!\n", tid);

  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  int i, scope;
  pthread_t tid[NUM_THREADS];
  pthread_attr_t attr;

  /* Get the default attributes */
  pthread_attr_init(&attr);

  /* first inquire on the current scope */
  if (pthread_attr_getscope(&attr, &scope) != 0) 
  {
    fprintf(stderr, "Unable to get scheduling scope \n");
  }
  else 
  {
    if (scope == PTHREAD_SCOPE_PROCESS)
      printf("PTHREAD_SCOPE_PROCESS");
    else if (scope == PTHREAD_SCOPE_SYSTEM) 
      printf("PTHREAD_SCOPE_SYSTEM");
    else 
      fprintf(stderr, "Illegal scope value.\n");
  }

  /* 
   * Set the scheduling algorithm to PCS or SCS 
   * PCS = Process Contention Scope - User-level threads
   * SCS = System Contention Scope - Kernel thread Sceduled 
   * Note: Linux and MacOS X only allow PTHREAD_SCOPE_SYSTEM
   */
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

  /* Create the threads */
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_create(&tid[i], &attr, PrintHello, NULL);
  }

  /* Join on each thread */
  for(i = 0; i < NUM_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }
}