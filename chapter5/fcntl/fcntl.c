#include <fcntl.h>
#include <sys/stat.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
  int input_fd, output_fd, open_flags;
  mode_t file_perms;
  ssize_t num_read;
  char buf[BUF_SIZE];

  if (argc != 2) {
    usageErr("%s file\n", argv[0]);
  }

  input_fd = open(argv[1], O_RDONLY);
  if (input_fd == -1) {
    errExit("opening file %s", argv[1]);
  }

  int flags = fcntl(input_fd, F_GETFL);
  int access_mode = flags & O_ACCMODE;
  printf("read? %d\n", access_mode == O_RDONLY);
  printf("async? %d\n", flags & O_ASYNC);

  if (close(input_fd) == -1) {
    errExit("close input");
  }
  exit(EXIT_SUCCESS);
}