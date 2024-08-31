#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <sys/io.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <unistd.h>

#define _BSD_SOURCE

int main() {
  const char *name1 =
      "/home/xufq/cpp/unix_program_interface/chapter18/chroot/chroot.c";
  const char *name2 = "/cpp/unix_program_interface/chapter18/chroot/chroot.c";
  char buff[100] = {0};
  memset(buff, 0, 100);
  {
    int fd = open(name1, O_RDONLY);
    read(fd, buff, 10);
    printf("%s\n", buff);
    memset(buff, 0, 100);
  }
  if (chroot("/home/xufq/")) {
    printf("change failed\n");
  }
  {
    int fd = open(name2, O_RDONLY);
    read(fd, buff, 10);
    printf("%s\n", buff);
    memset(buff, 0, 100);
  }
  return 0;
}
