#include <getopt.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/wait.h>
#include <tlpi_hdr.h>
#include <unistd.h>

#define BUF_SIZE 10

int main(int argc, char **argv) {
  int pfd[2];
  char buf[BUF_SIZE];
  ssize_t num_read;

  if (argc != 2) {
    usageErr("intput num error: %d\n", argc);
  }

  if (pipe(pfd) == -1)
    errExit("pipe");

  switch (fork()) {
  case -1:
    errExit("fork");
  case 0:
    if (close(pfd[1]) == -1)
      errExit("close child");
    while (1) {
      num_read = read(pfd[0], buf, BUF_SIZE);
      if (num_read == -1)
        errExit("read");
      if (num_read == 0) {
        printf("read end--------");
        fflush(stdout); // 不写入回车时需要显式刷新一下，否则停留在缓冲区中
        break;
      }
      if (write(STDOUT_FILENO, buf, num_read) != num_read)
        errExit("write partial failed");
      write(STDOUT_FILENO, "\n", 1);
    }
    if (close(pfd[0]) == -1)
      errExit("close");
    _exit(EXIT_SUCCESS);
  default:
    if (close(pfd[0]) == -1)
      errExit("close parent");
    if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
      errExit("parent partial write failed");

    if (close(pfd[1]) == -1)
      errExit("parent close failed");
    wait(NULL);
    exit(EXIT_SUCCESS);
  }
}
