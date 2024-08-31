#include <getopt.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/wait.h>
#include <tlpi_hdr.h>
#include <unistd.h>

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *threadProduct(void *arg) {
  while (glob < 10) {
    int s = pthread_mutex_lock(&mtx);
    if (s != 0)
      errExitEN(s, "pthread_mutex_lock");
    ++glob;
    s = pthread_mutex_unlock(&mtx);
    if (s != 0)
      errExitEN(s, "pthread_mutex_unlock");
    s = pthread_cond_signal(&cond);
    if (s != 0)
      errExitEN(s, "pthread_cond_signal");
    sleep(1);
  }
  return NULL;
}

static void *threadConsumer(void *arg) {
  int flag = 0;
  while (1) {
    int s = pthread_mutex_lock(&mtx);
    if (s != 0)
      errExitEN(s, "pthread_mutex_lock");
    while (glob == flag) {
      s = pthread_cond_wait(&cond, &mtx);
      if (s != 0)
        errExitEN(s, "pthread_cond_wait");
    }
    if (glob > 0)
      printf("%d\n", glob);
    if (glob >= 10) {
      s = pthread_mutex_unlock(&mtx);
      return NULL;
    }
    flag = glob;
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

  s = pthread_create(&t1, NULL, threadProduct, &loops);
  if (s != 0)
    errExitEN(s, "pthread_create");
  s = pthread_create(&t2, NULL, threadConsumer, &loops);
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
