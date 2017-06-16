#include "semafori.h"
key_t chiave;
int main (){
    chiave= ftok("semafori.h",3);
int idsem=createSem(chiave,1,IPC_CREAT);
init(idsem,0,1);
semWait(idsem,0);
printf("ora tocca a me");
semSignal(idsem,0);    
}
