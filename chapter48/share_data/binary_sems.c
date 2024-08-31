#include "binary_sems.h"
#include "semun.h"
#include <sys/sem.h>
#include <sys/types.h>

Boolean bsUseSemUndo = FALSE;
Boolean bsRetryOnEintr = TRUE;

int InitSemAvailable(int sem_id, int sem_num) {
  union semun arg;
  arg.val = 1;
  return semctl(sem_id, sem_num, SETVAL, arg);
}

int InitSemInUse(int sem_id, int sem_num) {
  union semun arg;
  arg.val = 0;
  return semctl(sem_id, sem_num, SETVAL, arg);
}

int ReserveNum(int sem_id, int sem_num) {
  struct sembuf sops;

  sops.sem_num = sem_num;
  sops.sem_op = -1;
  sops.sem_flg = bsUseSemUndo ? SEM_UNDO : 0;

  while (semop(sem_id, &sops, 1) == -1) {
    if (errno != EINTR || !bsRetryOnEintr) {
      return -1;
    }
  }
  return 0;
}

int ReleaseNum(int sem_id, int sem_num) {
  struct sembuf sops;

  sops.sem_num = sem_num;
  sops.sem_op = 1;
  sops.sem_flg = bsUseSemUndo ? SEM_UNDO : 0;

  while (semop(sem_id, &sops, 1) == -1) {
    if (errno != EINTR || !bsRetryOnEintr) {
      return -1;
    }
  }
  return 0;
}
