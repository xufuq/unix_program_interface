#include <getopt.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/wait.h>
#include <tlpi_hdr.h>
#include <unistd.h>

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *threadFunc(void *arg) {
  int loops = *((int *)arg);
  int loc, j, s;
  for (j = 0; j < loops; ++j) {
    s = pthread_mutex_lock(&mtx);
    if (s != 0)
      errExitEN(s, "pthread_mutex_lock");
    loc = glob;
    ++loc;
    glob = loc;
    s = pthread_mutex_unlock(&mtx);
    if (s != 0)
      errExitEN(s, "pthread_mutex_unlock");
  }
  return NULL;
}

int main(int argc, char **argv) {
  pthread_t t1, t2;
  int loops, s;
  loops = 10000000;

  s = pthread_create(&t1, NULL, threadFunc, &loops);
  if (s != 0)
    errExitEN(s, "pthread_create");
  s = pthread_create(&t2, NULL, threadFunc, &loops);
  if (s != 0)
    errExitEN(s, "pthread_create");

  s = pthread_join(t1, NULL);
  if (s != 0)
    errExitEN(s, "pthread_join");
  s = pthread_join(t2, NULL);
  if (s != 0)
    errExitEN(s, "pthread_join");

  printf("glob = %d\n", glob);
  exit(EXIT_SUCCESS);
}
