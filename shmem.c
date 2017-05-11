#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  char string[4];
  char *p;
  int shmid;

  shmid=shmget(IPC_PRIVATE, sizeof(string[4]), 0666 | IPC_CREAT);   //crea una zona di memoria condivisa
  p=(char *)shmat(shmid, NULL, 0);                                  //si "attacca" tramite un puntatore alla zona di memoria appena creata

  pid_t child= fork();                                              //crea un processo figlio
  if (child<0) {
    perror("Fork fallita");
    exit(-1);
  }

  else if ((int)child==0) {                                         //viene eseguito dal processo figlio
    p[0]='p'; p[1]='a'; p[2]='p'; p[3]='i';
    shmdt(p);                                                       //si "stacca" dalla zona di memoria condivisa
  }

  else {                                                            //viene eseguito dal processo padre
    if(wait(NULL)==-1) {
      perror("Wait fallita");
      exit(-1);
    }
    for(int i=0; i<4; i++) {
      printf("%c", p[i]);
    }
    shmdt(p);                                                       //si "stacca" dalla zona di memoria condivisa
    shmctl(shmid, IPC_RMID, 0);                                     //elimina la zona di memoria condivisa
    exit(0);
  }
}
