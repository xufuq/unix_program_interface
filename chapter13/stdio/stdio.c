#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

#include "tlpi_hdr.h"

int main() {
  FILE *fp = fopen("./test.txt", "w");
  if (fp == NULL) {
    errExit("fopen");
  }
  char buf[1024];
  int ret = setvbuf(fp, buf, _IOLBF, 1024);
  if (ret != 0) {
    errExit("setvbuf");
  }
  fprintf(fp, "this is a test\n");
  printf("%s\n", buf);
  fprintf(fp, "test\n");
  printf("%s\n", buf);
  fflush(fp);
  fclose(fp);
  FILE *fp2 = fopen("./test2.txt", "w");
  ret = setvbuf(fp2, buf, _IOFBF, 1024);
  if (ret != 0) {
    errExit("setvbuf");
  }
  fprintf(fp2, "test\n");
  fprintf(fp2, "this is a test\n");
  buf[4] = 'g';
  printf("%s\n", buf);
  fclose(fp2);
  return 0;
}