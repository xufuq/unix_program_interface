#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <tlpi_hdr.h>

#define SYNC_SIG SIGUSR1

static void handler(int sig) {
  printf("this is a handler of [%s]\n", strsignal(sig));
}

int main() {
  pid_t child_pid;
  sigset_t block_mask, orig_mask, empty_mask;
  struct sigaction sa;

  setbuf(stdout, NULL);

  sigemptyset(&block_mask);
  sigaddset(&block_mask, SYNC_SIG);
  if (sigprocmask(SIG_BLOCK, &block_mask, &orig_mask)) {
    errExit("sigprocmask");
  }

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = handler;
  if (sigaction(SYNC_SIG, &sa, NULL) == -1) {
    errExit("sigaction");
  }

  switch (child_pid = fork()) {
    case -1: { errExit("atexit"); }
    case 0: {
      time_t ttm = time(NULL);
      printf("[%ld %d] child started - doing some work\n", ttm, getpid());
      sleep(2);
      ttm = time(NULL);
      printf("[%ld %d] child exit - done\n", ttm, getpid());
      if (kill(getppid(), SYNC_SIG) == -1) {
        errExit("kill");
      }
      _exit(EXIT_SUCCESS);
    }
    default: {
      time_t ttm = time(NULL);
      printf("[%ld %d] parent wait for signal\n", ttm, getpid());
      sigemptyset(&empty_mask);
      // 可以将进程掩码替换为当前并等待信号到来，之后回复原来的掩码
      if (sigsuspend(&empty_mask) == -1 && errno != EINTR) {
        errExit("sigsuspend");
      }
      ttm = time(NULL);
      printf("[%ld %d] parent got signal\n", ttm, getpid());

      if (sigprocmask(SIG_SETMASK, &orig_mask, NULL) == -1) {
        errExit("sigprocmask");
      }
      exit(EXIT_SUCCESS);
    }
  }
}
