#include <unistd.h>
#include <stdint.h>
#include <tlpi_hdr.h>

void AtExit() {
  printf("atexit\n");
}

void OnExit(int status, void *arg) {
  printf("%d %s\n", status, (char *) arg);
}

int main() {
  atexit(AtExit);
  on_exit(OnExit, (void *)(" a test"));
  exit(1);
}
