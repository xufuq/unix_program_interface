#include <stdio.h>
#include <unistd.h>

int main() {
  printf("pid: %ld\n", getpid());
  printf("ppid: %ld\n", getppid());
  return 0;
}