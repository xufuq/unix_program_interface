#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

#include "tlpi_hdr.h"

int main() {
  FILE *stream = fdopen(STDOUT_FILENO, "w");
  if (stream == NULL) {
    errExit("fdopen");
  }
  fprintf(stream, "fprintf\n");
  fprintf(stdout, "fprintf2\n");
  int fd = fileno(stream);
  write(fd, "write\n", 6);
  return 0;
}