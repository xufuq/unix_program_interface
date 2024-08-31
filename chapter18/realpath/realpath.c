#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <unistd.h>

#define _BSD_SOURCE

int main() {
  const char *name = "chapter18/chroot/chroot.c";
  char buff[100] = {0};
  char *ret = realpath(name, buff);
  printf("%s\n", ret);
  return 0;
}
