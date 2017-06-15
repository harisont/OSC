#include "semafori.h"
key_t chiave;
int main (){
    chiave= ftok("semafori.h",3);
int idsem=createSem(chiave,1,IPC_CREAT);
init(idsem,0,1);
semWait(idsem,0);
for (int i=0;i<100;i++)
	printf("%d tocca a me",i);
semSignal(idsem,0);    
}
