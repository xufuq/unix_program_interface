#include <unistd.h>
#include <stdint.h>
#include <getopt.h>
#include <sys/wait.h>
#include <tlpi_hdr.h>

void PrintWaitStatus(const char *msg, int status) {
  if (msg != NULL) { printf("%s ", msg); }
  else if (WIFEXITED(status)) { printf("child exited, status = %d\n", WEXITSTATUS(status)); }
  else if (WIFSIGNALED(status)) {
    printf("child killed by signal %d (%s), CoreDump = %d\n",
           WTERMSIG(status),
           strsignal(WTERMSIG(status)),
           WCOREDUMP(status));
  } else if (WIFSTOPPED(status)) {
    printf("child stopped by signal %d (%s)\n",
           WTERMSIG(status),
           strsignal(WTERMSIG(status)));
  } else if (WIFCONTINUED(status)) { printf("child continued\n"); }
  else { printf("unknown happened\n"); }
}

int main(int argc, char **argv) {
  int status;
  pid_t child_pid;
  switch (fork()) {
    case -1:errExit("fork");

    case 0: {
      printf("child_pid: %d\n", getpid());
      if (argc > 1) {
        exit(strtol(argv[1], argv[2], 10));
      } else {
        while (1) {
          pause();
        }
        exit(EXIT_SUCCESS);
      }
    }
    default:
      while (1) {
        child_pid = waitpid(-1, &status, WUNTRACED | WCONTINUED);
        if (child_pid == -1) {
          errExit("waitpid");
        }
        printf("waitpid() returned: PID=%ld; status=0x%04x (%d,%d)\n", child_pid, status, status >> 8, status & 0xff);
        PrintWaitStatus(NULL, status);
        if (WIFEXITED(status) | WIFSIGNALED(status)) {
          exit(EXIT_SUCCESS);
        }
      }
  }
}
