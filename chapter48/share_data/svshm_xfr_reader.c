#include "svshm_xfr.h"

int main(int argc, char *argv[]) {
  int semid, shmid, xfrs, bytes;
  struct shmseg *shmp;

  semid = semget(SEM_KEY, 0, 0);
  if (semid == -1) {
    errExit("semget");
  }
  shmid = shmget(SHM_KEY, 0, 0);
  if (shmid == -1) {
    errExit("shmget");
  }
  shmp = (struct shmseg *)shmat(shmid, NULL, SHM_RDONLY);
  if (shmp == (void *)-1) {
    errExit("shmat");
  }

  for (xfrs = 0, bytes = 0;; xfrs++) {
    if (ReserveNum(semid, READ_SEM) == -1) {
      errExit("ReserveNum");
    }
    if (shmp->cnt == 0) {
      break;
    }
    bytes += shmp->cnt;

    if (write(STDOUT_FILENO, shmp->buf, shmp->cnt) != shmp->cnt) {
      fatal("partial/failed write");
    }
    if (ReleaseNum(semid, WRITE_SEM) == -1) {
      errExit("ReleaseSem");
    }
  }
  if (shmdt(shmp) == -1) {
    errExit("shmdt");
  }
  if (ReleaseNum(semid, WRITE_SEM) == -1) {
    errExit("ReleaseSem");
  }
  fprintf(stderr, "received %d bytes (%d xfrs)\n", bytes, xfrs);
  exit(EXIT_SUCCESS);
}