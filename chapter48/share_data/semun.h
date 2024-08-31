
#ifndef UNIXPROGRAMINTERFACE_CHAPTER48_SHARE_DATA_SEMUN_H_
#define UNIXPROGRAMINTERFACE_CHAPTER48_SHARE_DATA_SEMUN_H_

#include <sys/sem.h>
#include <sys/types.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

#endif // UNIXPROGRAMINTERFACE_CHAPTER48_SHARE_DATA_SEMUN_H_
