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
  const char *name3 = "3.txt";
  int fd1 = open(name1, O_CREAT | O_RDWR, S_IRWXU);
  link(name1, name2);
  int fd2 = open(name2, O_RDWR);
  link(name1, name3);
  int fd3 = open(name3, O_RDWR);
  write(fd1, "fd1 ", 4);
  lseek(fd2, 0, SEEK_END);
  write(fd2, "fd2 l", 5);
  char buff[100];
  read(fd3, buff, 100);
  printf("fd3 content: %s\n", buff);
  lseek(fd1, 0, SEEK_SET);
  memset(buff, 0, 100);
  read(fd1, buff, 100);
  printf("fd1 content: %s\n", buff);
  close(fd1);
  close(fd2);
  close(fd3);
  return 0;
}
