#include "tlpi_hdr.h"
#include "us_xfs_sv.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define BACKLOG 5

int main(int argc, char *argv[]) {
  struct sockaddr_un addr;
  ssize_t num_read;
  char buff[BUF_SIZE];
  int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sfd == -1) {
    errExit("socket");
  }

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  if (connect(sfd, (struct sockaddr *)(&addr), sizeof(struct sockaddr_un)) ==
      -1) {
    errExit("connect");
  }
  while ((num_read = read(STDIN_FILENO, buff, BUF_SIZE)) > 0) {
    if (write(sfd, buff, num_read) != num_read) {
      errExit("write");
    }
    if (strcmp("exit-client\n", buff) == 0) {
      exit(EXIT_SUCCESS);
    }
  }
  exit(EXIT_SUCCESS);
}
