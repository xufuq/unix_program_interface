#include <getopt.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/wait.h>
#include <tlpi_hdr.h>
#include <unistd.h>

static void *threadFunc(void *arg) {
  char *s = (char *)arg;
  printf("%s", s);
  return (void *)strlen(s);
}

int main(int argc, char **argv) {
  pthread_t td;
  void *res;
  int s;

  s = pthread_create(&td, NULL, threadFunc, "Hello World\n");
  if (s != 0) {
    errExitEN(s, "pthread_create");
  }

  printf("Message from main()\n");
  s = pthread_join(td, &res);
  printf("%ld\n", (long)res);
  exit(EXIT_SUCCESS);
}
