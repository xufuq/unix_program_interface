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

  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s old_file new_file\n", argv[0]);
  }

  input_fd = open(argv[1], O_RDONLY);
  if (input_fd == -1) {
    errExit("opening file %s", argv[1]);
  }

  open_flags = O_CREAT | O_WRONLY | O_TRUNC;  // 新建，只写，丢弃原本内容
  file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IWOTH |
               S_IROTH;  // "rw-rw-rw" 文件权限
  output_fd = open(argv[2], open_flags, file_perms);
  if (output_fd == -1) {
    errExit("opening file %s", argv[2]);
  }

  int i = 2;
  while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0) {
    printf("copy %ld bytes\n", num_read);
    if (write(output_fd, buf, num_read) != num_read) {
      fatal("couldn't write whole buffer");
    }
    if (i > 0) {
      off_t cur = lseek(input_fd, 0, SEEK_SET);
      --i;
    }
  }
  if (num_read == -1) {
    errExit("read");
  }
  if (close(input_fd) == -1) {
    errExit("close input");
  }
  if (close(output_fd) == -1) {
    errExit("close output");
  }
  exit(EXIT_SUCCESS);
}