#ifndef UNIXPROGRAMINTERFACE_CHAPTER48_SHARE_DATA_SVSHM_XFR_H_
#define UNIXPROGRAMINTERFACE_CHAPTER48_SHARE_DATA_SVSHM_XFR_H_

#include "binary_sems.h"
#include "tlpi_hdr.h"
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SEM_KEY 0x1234
#define SHM_KEY 0x5678

#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

#define WRITE_SEM 0
#define READ_SEM 1

#ifndef BUF_SIZE
#define BUF_SIZE 10
#endif

struct shmseg {
  int cnt;
  char buf[BUF_SIZE];
};

#endif // UNIXPROGRAMINTERFACE_CHAPTER48_SHARE_DATA_SVSHM_XFR_H_
