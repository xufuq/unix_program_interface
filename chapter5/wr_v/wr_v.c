#include <fcntl.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

typedef struct {
  char a;
  u_int32_t b;
} wr_v;

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

  double x = 1.5;
  wr_v y = {1, 255};
  char str[] = "test v";

  struct iovec iov[3];
  iov[0].iov_base = &x;
  iov[0].iov_len = sizeof(x);
  iov[1].iov_base = &y;
  iov[1].iov_len = sizeof(y);
  iov[2].iov_base = str;
  iov[2].iov_len = sizeof(str);

  ssize_t s = pwritev(input_fd, iov, 3, 10);
  if (s != sizeof(x) + sizeof(y) + 7) {
    printf("few write\n");
  }

  struct iovec iov2[3];
  double xx;
  wr_v yy;
  char str2[7];
  iov2[0].iov_base = &xx;
  iov2[0].iov_len = sizeof(xx);
  iov2[1].iov_base = &yy;
  iov2[1].iov_len = sizeof(yy);
  iov2[2].iov_base = str2;
  iov2[2].iov_len = 7;

  s = preadv(input_fd, iov2, 3, 10);
  if (s != sizeof(x) + sizeof(y) + 7) {
    printf("few write\n");
  }

  if ((*(double *)(iov2[0].iov_base)) != x ||
      ((wr_v *)(iov2[1].iov_base))->a != y.a ||
      ((wr_v *)(iov2[1].iov_base))->b != y.b ||
      strcmp(str, iov2[2].iov_base) != 0) {
    printf("read error\n");
  }
  if (close(input_fd) == -1) {
    errExit("close input");
  }
  exit(EXIT_SUCCESS);
}