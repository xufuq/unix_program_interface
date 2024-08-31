#include "tlpi_hdr.h"
#include "us_xfs_sv.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define BACKLOG 5

int main(int argc, char *argv[]) {
  struct sockaddr_in svaddr, claddr;
  int sfd, j;
  ssize_t num_bytes;
  socklen_t len;
  char buf[BUF_SIZE];
  char claddrStr[INET6_ADDRSTRLEN];

  sfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sfd == -1) {
    errExit("socket");
  }
  memset(&svaddr, 0, sizeof(struct sockaddr_in));
  svaddr.sin_family = AF_INET;
  //  if (inet_pton(AF_INET, "127.0.0.1", &svaddr.sin_addr) != 1) {
  //    errExit("inet_pton");
  //  }
  //  if (inet_pton(AF_INET, "127.255.255.255", &svaddr.sin_addr) != 1) {
  //    errExit("inet_pton");
  //  }
  svaddr.sin_addr.s_addr = htons(INADDR_ANY);
  svaddr.sin_port = htons(PORT_NUM);

  if (bind(sfd, (struct sockaddr const *)&svaddr, sizeof(struct sockaddr_in))) {
    errExit("bind");
  }

  for (;;) {
    len = sizeof(struct sockaddr_in);
    num_bytes =
        recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len);
    if (num_bytes == -1) {
      errExit("recvfrom");
    }
    if (inet_ntop(AF_INET, &claddr.sin_addr, claddrStr, INET6_ADDRSTRLEN) ==
        NULL) {
      errExit("inet_ntop");
    }
    printf("client ip: %s\n", claddrStr);

    for (j = 0; j < num_bytes; ++j) {
      buf[j] = toupper(buf[j]);
    }
    if (sendto(sfd, buf, num_bytes, 0, (struct sockaddr *)&claddr,
               sizeof(struct sockaddr_in)) != num_bytes) {
      fatal("sendto");
    }
  }
}
