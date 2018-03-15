#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

void *runner(void *threadid) {
  printf("Do some work... %ld \n", (long) threadid);
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  int i, policy;
  pthread_t tid[NUM_THREADS];
  pthread_attr_t attr;

  /* Get the default attributes */
  pthread_attr_init(&attr);

  /* Get the current sceduling policy */
  if (pthread_attr_getschedpolicy(&attr, &policy) != 0) 
  {
    fprintf(stderr, "Unable to get policy.\n");
  }
  else 
  {
    if (policy == SCHED_OTHER) printf("SCHED_OTHER\n");
    else if (policy == SCHED_RR) printf("SCHED_RR\n");
    else if (policy == SCHED_FIFO) printf("SCHED_FIFO\n");
  }

  /* 
   * Set the scheduling policy - FIFO, RR, or OTHER
   */
  if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
    fprintf(stderr, "Unable to set policy.\n");
  }

  if (policy == SCHED_OTHER) printf("SCHED_OTHER\n");
    else if (policy == SCHED_RR) printf("SCHED_RR\n");
    else if (policy == SCHED_FIFO) printf("SCHED_FIFO\n");

  /* Create the threads */
  long x;
  for(i = 0; i < NUM_THREADS; i++) {
    pthread_create(&tid[i], &attr, runner, (void *) x);
    x++;
  }

  /* Join on each thread */
  for(i = 0; i < NUM_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }
}
