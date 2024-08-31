#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("_SC_OPEN_MAX: %ld\n", sysconf(_SC_OPEN_MAX));
  printf("_SC_ARG_MAX: %ld\n", sysconf(_SC_ARG_MAX));
  //   printf("_SC_ARG_MAX: %d\n", _P);
}