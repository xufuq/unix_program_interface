#ifndef BINARY_SEM
#define BINARY_SEM

#include "tlpi_hdr.h"

extern Boolean bsUseSemUndo;
extern Boolean bsRetryOnEintr;

int InitSemAvailable(int sem_id, int sem_num);

int InitSemInUse(int sem_id, int sem_num);

int ReserveSem(int sem_id, int sem_num);

int ReleaseSem(int sem_id, int sem_num);

#endif