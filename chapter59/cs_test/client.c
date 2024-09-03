#include "is_seqnum.h"
#include <netdb.h>

int main(int argc, char *argv[]) {
  char *req_len_str;
  char seq_num_str[INT_LEN];
  int cfd;
  ssize_t num_read;
  struct addrinfo hints;
  struct addrinfo *result, *rp;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV;

  if (getaddrinfo(argv[1], PORT_NUM, &hints, &result) != 0) {
    errExit("getaddrinfo");
  }
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    cfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (cfd == -1) {
      continue;
    }
    if (connect(cfd, (struct sockaddr *)rp->ai_addr, rp->ai_addrlen) != -1) {
      break;
    }
    close(cfd);
  }
  if (rp == NULL) {
    fatal("Could not connect socket to any address");
  }
  freeaddrinfo(result);

  req_len_str = argc > 2 ? argv[2] : "1";
  if (write(cfd, req_len_str, strlen(req_len_str)) != strlen(req_len_str)) {
    fatal("Partial write");
  }

  memset(seq_num_str, 0, INT_LEN);
  num_read = read(cfd, seq_num_str, 3);
  if (num_read == -1) {
    errExit("exit");
  } else if (num_read == 0) {
    errExit("unexpected EOF");
  }
  printf("Sequence number: %s\n", seq_num_str);
  exit(EXIT_SUCCESS);
}