#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main() {
  printf("\nSono un processo con pid %d.\n", (int)getpid());
  pid_t child= fork();      //genera un figlio

  if (child<0) {            //controlla l'efficacia della fork()
    perror("Fork fallita");
    exit(-1);
  }

  else if ((int)child==0) { //viene eseguito dal processo figlio
    printf("Sono %d, figlio di %d.\n", (int)getpid(), (int)getppid());
  }

  else {                    //viene eseguito dal processo padre
    printf("Sono ancora %d.\n", (int)getpid());
    if(wait(NULL)==-1) {
      perror("Wait fallita");
      exit(-1);
    }
    printf("Sono %d, sono tornato.\n\n", (int)getpid());
    exit(0);
  }

}
