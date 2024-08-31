#include "tlpi_hdr.h"

extern Boolean bsUseSemUndo;
extern Boolean bsRetryOnEintr;

int InitSemAvailable(int sem_id, int sem_num);

int InitSemInUse(int sem_id, int sem_num);

int ReserveNum(int sem_id, int sem_num);

int ReleaseNum(int sem_id, int sem_num);