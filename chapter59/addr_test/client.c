#include "tlpi_hdr.h"
#include "us_xfs_sv.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define BACKLOG 5

int main(int argc, char *argv[]) {
  struct sockaddr_in svaddr;
  int sfd, j;
  size_t num_bytes;
  char resp[BUF_SIZE];

  sfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sfd == -1) {
    errExit("socket");
  }

  memset(&svaddr, 0, sizeof(struct sockaddr_in));
  svaddr.sin_family = AF_INET;
  svaddr.sin_port = htons(PORT_NUM);
  if (inet_pton(AF_INET, argv[1], &svaddr.sin_addr) != 1) {
    errExit("inet_pton");
  }

  int opt = 1;
  if (setsockopt(sfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) < 0) {
    errExit("setsocket");
  }

  for (j = 2; j < argc; ++j) {
    if (sendto(sfd, argv[j], strlen(argv[j]), 0, (struct sockaddr *)&svaddr,
               sizeof(struct sockaddr_in)) != strlen(argv[j])) {
      errExit("sendto");
    }
    num_bytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
    if (num_bytes == -1) {
      errExit("recvfrom");
    }
    printf("Response %d: %.*s\n", j - 1, (int)num_bytes, resp);
  }
  exit(EXIT_SUCCESS);
}
