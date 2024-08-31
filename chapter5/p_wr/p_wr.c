#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
  int input_fd, output_fd, open_flags;
  mode_t file_perms;
  ssize_t num_read;
  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);

  if (argc != 2) {
    usageErr("%s file\n", argv[0]);
  }

  input_fd = open(argv[1], O_RDWR);
  if (input_fd == -1) {
    errExit("opening file %s", argv[1]);
  }

  ssize_t s = pread(input_fd, buf, 3, 3);
  printf("%ld, %s\n", s, buf);
  printf("%ld\n", lseek(input_fd, 0, SEEK_CUR));
  memset(buf, 0, BUF_SIZE);
  read(input_fd, buf, 3);
  printf("%ld, %s\n", s, buf);
  printf("%ld\n", lseek(input_fd, 0, SEEK_CUR));

  if (close(input_fd) == -1) {
    errExit("close input");
  }
  exit(EXIT_SUCCESS);
}