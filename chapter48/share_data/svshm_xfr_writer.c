#include "semun.h"
#include "svshm_xfr.h"

int main(int argc, char *argv[]) {
  int semid, shmid, bytes, xfrs;
  struct shmseg *shmp;
  union semun dummy;

  semid = semget(SEM_KEY, 2, IPC_CREAT | OBJ_PERMS);
  if (semid == -1) {
    errExit("semget");
  }
  if (InitSemAvailable(semid, WRITE_SEM) == -1) {
    errExit("InitSemAbailable");
  }
  if (InitSemInUse(semid, READ_SEM) == -1) {
    errExit("InitSemInUse");
  }

  shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | OBJ_PERMS);
  if (shmid == -1) {
    errExit("shmget");
  }
  shmp = shmat(shmid, NULL, 0);
  if (shmp == (void *)-1) {
    errExit("shmat");
  }

  for (xfrs = 0, bytes = 0;; xfrs++, bytes += shmp->cnt) {
    if (ReserveNum(semid, WRITE_SEM) == -1) {
      errExit("ReserveNum");
    }

    shmp->cnt = read(STDIN_FILENO, shmp->buf, BUF_SIZE);
    if (shmp->cnt == -1) {
      errExit("read");
    }

    if (ReleaseNum(semid, READ_SEM) == -1) {
      errExit("ReleaseNum");
    }

    if (shmp->cnt == 0) {
      break;
    }
  }

  if (ReserveNum(semid, WRITE_SEM) == -1) {
    errExit("ReserveNum");
  }

  if (semctl(semid, 0, IPC_RMID, dummy) == -1) { // 删除信号量集
    errExit("semctl");
  }
  if (shmdt(shmp) == -1) { // 分离共享内存
    errExit("shmdt");
  }
  if (shmctl(shmid, IPC_RMID, 0) == -1) { // 删除共享内存对象
    errExit("shmctl");
  }

  fprintf(stderr, "Sent %d bytes (%d xfrs\n", bytes, xfrs);
  exit(EXIT_SUCCESS);
}