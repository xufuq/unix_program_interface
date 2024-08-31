#include "tlpi_hdr.h"
#include "us_xfs_sv.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define BACKLOG 5

int main(int argc, char *argv[]) {
  struct sockaddr_un svaddr, claddr;
  int sfd, j;
  size_t msg_len;
  ssize_t msg_bytes;
  char resp[BUF_SIZE];

  sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sfd == -1) {
    errExit("socket");
  }

  memset(&claddr, 0, sizeof(struct sockaddr_un));
  claddr.sun_family = AF_UNIX;
  snprintf(claddr.sun_path, sizeof(claddr.sun_path), "/tmp/ud_ucase_cl.%ld",
           (long)getpid());
  if (bind(sfd, (struct sockaddr_un *)(&claddr), sizeof(struct sockaddr_un)) ==
      -1) {
    errExit("bind");
  }

  memset(&svaddr, 0, sizeof(struct sockaddr_un));
  svaddr.sun_family = AF_UNIX;
  strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

  for (;;) {
    msg_len = read(STDIN_FILENO, resp, BUF_SIZE);
    if (sendto(sfd, resp, msg_len, 0, (struct sockaddr_un *)(&svaddr),
               sizeof(struct sockaddr_un)) == -1) {
      errExit("sendto");
    }
    if (strcmp("exit-client\n", resp) == 0) {
      exit(EXIT_SUCCESS);
    }
  }
}
