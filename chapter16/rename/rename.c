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
  rename(name1, name2);
  return 0;
}
