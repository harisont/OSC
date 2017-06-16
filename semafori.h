#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>

int createSem(key_t chiave, int numSem, int flag);
int init(int idSem, int num, int cmd);
int semWait(int idSem,int num);
int semSignal(int idSem,int num);
