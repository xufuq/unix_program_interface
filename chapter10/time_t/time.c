#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main() {
  struct timeval td;
  int r = gettimeofday(&td, NULL);
  if (r == 0) {
    printf("%ld.%ld\n", td.tv_sec, td.tv_usec);
  }
  time_t t = time(NULL);
  printf("%ld\n", (long)(t));
  printf("%s\n", ctime(&t));
  return 0;
}