#include <stdio.h>
#include <time.h>
#include <tlpi_hdr.h>

#define _XOPEN_SOURCE 600

int main() {
  struct timespec request;
  if (clock_gettime(CLOCK_REALTIME, &request) == -1) {
    errExit("clock_gettime");
  }
  printf("%ld\n", request.tv_sec);
  request.tv_sec += 10;
  int s = clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &request, NULL);
  if (s != 0) {
    errExit("nanosleep");
  }
  printf("%ld\n", request.tv_sec);
  return 0;
}
