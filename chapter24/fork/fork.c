#include <unistd.h>
#include <stdint.h>
#include <tlpi_hdr.h>

static uint32_t idata = 1;

int main() {
  uint32_t is = 2;
  pid_t child_pid;
  switch (child_pid = fork()) {
    case -1: errExit("atexit");
    case 0:
      idata *= 3;
      is    *= 3;
      break;
    default:
      idata *= 4;
      is    *= 4;
      break;
  }
  printf("PID %10d %s idata: %d is: %d\n", child_pid, child_pid == 0 ? "parent" : "child ", idata, is);
  return 0;
}
