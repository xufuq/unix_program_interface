#include "is_seqnum.h"
#include <netdb.h>

#define BACKLOG 50
#define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)

int main(int argc, char *argv[]) {
  uint32_t seq_num;
  char req_len_str[INT_LEN];
  char seq_num_str[INT_LEN];
  struct sockaddr_storage cl_addr;
  int lfd, cfd, opt_val, req_len;
  socklen_t addr_len;
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  char add_str[ADDRSTRLEN];
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];

  seq_num = atoi(argv[1]);
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    errExit("signal");
  }
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
  if (getaddrinfo(NULL, PORT_NUM, &hints, &result) != 0) {
    errExit("getaddrinfo");
  }

  opt_val = 1;
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (lfd == -1) {
      continue;
    }
    if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)) ==
        -1) {
      errExit("setsockopt");
    }
    if (bind(lfd, (struct sockaddr *)rp->ai_addr, rp->ai_addrlen) == 0) {
      break;
    }
    close(lfd);
  }

  if (rp == NULL) {
    fatal("couldn't bind socket to any address");
  }

  if (listen(lfd, BACKLOG) == -1) {
    errExit("listen");
  }
  freeaddrinfo(result);

  for (;;) {
    addr_len = sizeof(struct sockaddr_storage);
    cfd = accept(lfd, (struct sockaddr *)&cl_addr, &addr_len);
    if (cfd == -1) {
      errMsg("accept");
      continue;
    }

    if (getnameinfo((struct sockaddr *)&cl_addr, addr_len, host, NI_MAXHOST,
                    service, NI_MAXSERV, 0) == 0) {
      snprintf(add_str, ADDRSTRLEN, "(%s, %s)", host, service);
    } else {
      snprintf(add_str, ADDRSTRLEN, "(?UNKNOWN?)");
    }
    printf("Connecton from %s\n", add_str);

    if (read(cfd, req_len_str, 3) <= 0) {
      continue;
      close(cfd);
    }
    req_len = atoi(req_len_str);
    if (req_len <= 0) {
      close(cfd);
      continue;
    }
    memset(seq_num_str, 0, INT_LEN);
    printf("cur seq: %d, recv seq:%d\n", seq_num, req_len);
    snprintf(seq_num_str, INT_LEN, "%d", seq_num);
    if (write(cfd, seq_num_str, strlen(seq_num_str)) != strlen(seq_num_str)) {
      fprintf(stderr, "Error on write");
    }
    seq_num += req_len;
    if (close(cfd) == -1) {
      errMsg("close");
    }
  }
}