#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  struct addrinfo hints, *result, *rp;
  int err;
  char ipstr[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC; // 不限制IP协议版本
  hints.ai_socktype = SOCK_STREAM;

  if ((err = getaddrinfo(argv[1], NULL, &hints, &result)) != 0) {
    printf("getaddrinfo error: %s\n", gai_strerror(err));
    return -1;
  }
  printf("request IP of %s:\n", argv[1]);

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    void *addr;
    char *ipver;

    if (rp->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
      addr = &ipv4->sin_addr;
      ipver = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
      addr = &ipv6->sin6_addr;
      ipver = "IPv6";
    }
    inet_ntop(rp->ai_family, addr, ipstr, INET6_ADDRSTRLEN);
    printf("  %s: %s\n", ipver, ipstr);
  }
  freeaddrinfo(result);
  exit(EXIT_SUCCESS);
}