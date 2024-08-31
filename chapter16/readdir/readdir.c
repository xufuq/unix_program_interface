#include <dirent.h>
#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <sys/io.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <unistd.h>

int main() {
  const char path[] = "/home/xufq/cpp/unix_program_interface";
  DIR *dir = opendir(path);
  struct dirent *item = NULL;
  while (item = readdir(dir)) {
    printf("name: %-20s id: %ld\n", item->d_name, item->d_ino);
  }
  return 0;
}
