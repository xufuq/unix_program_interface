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
  char path[200];
  const char *ret = getcwd(path, 200);
  if (ret != NULL) {
    printf("CurPath: %s\n", ret);
  }
  const char newpath[] = "/home/xufq/cpp/unix_program_interface/chapter15/stat";
  chdir(newpath);
  ret = getcwd(path, 200);
  if (ret != NULL) {
    printf("NewPath: %s\n", ret);
  }
  return 0;
}
