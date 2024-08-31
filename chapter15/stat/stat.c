#include <stdio.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <unistd.h>

int main() {
  struct stat inode;
  stat("/home/xufq/cpp/unix_program_interface", &inode);
  printf("size: %ld\n", inode.st_size);
  printf("blocksize: %ld\n", inode.st_blksize);
  printf("blocks: %ld\n", inode.st_blocks);
  printf("nlink: %ld\n", inode.st_nlink);
  return 0;
}