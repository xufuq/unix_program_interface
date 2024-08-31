#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <sys/io.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <unistd.h>

int main() {
  const char *name1 = "1.txt";
  const char *name2 = "2.txt";
  symlink(name1, name2);
  int fd1 = open(name1, O_RDWR);
  char buff[100];
  read(fd1, buff, 100);
  printf("read: %s\n", buff);
  memset(buff, 0, 100);
  readlink(name2, buff, 100);
  printf("readlink: %s\n", buff);
  return 0;
}
