#include "semafori.h"

// libreria semafori
int createSem(key_t chiave, int numSem, int flag){  //crea i un array di seafori lungo numSem

    int idSem = semget(chiave,numSem, flag);         
    if (idSem == -1){
        perror("createSem fallita");
        exit(1);
    }
    else return(idSem);
    
}

int init(int idSem, int num, int cmd){         // permette di inizializzare un semaforo
    int temp=semctl(idSem, num,SETVAL,cmd);
        if (temp== -1){
            perror("init non ha funzionato");
            exit(1);
         }
        else return(temp);
}

int semWait(int idSem,int num){    // wait  ovvio
    struct sembuf valore;
    unsigned nsops=0;
    valore.sem_num=num;
    valore.sem_op=-1;
    int analisi=semop(idSem, &valore, nsops);
    if (analisi == -1){
         perror("semWait non ha funzionato");
         exit(1);
    }
    else return(analisi);
}

int semSignal(int idSem,int num){   // signal ovvio
   struct sembuf valore;
   unsigned nsops=0;
   valore.sem_num=num;
   valore.sem_op=1;
   int analisi=semop(idSem, &valore, nsops);
   if (analisi==-1){
       perror("semSignal non ha funzionato ");
       exit(1);
   }       
   else return(analisi);
}
