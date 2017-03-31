#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  if(argc!=2) {
    perror("Per utilizzare il programma, digitare il nome del comando seguito dalla riga da trasmettere.\n");
    exit(EXIT_FAILURE);                         /*utilizzando EXIT_FAILURE al posto di un valore numerico esplicito
                                                  il codice è più portabile*/
  }
  int tubofd[2];                                //tubofd conterrà i descrittori delle due estremità del "tubo"
  char buffer;
  int tubo=pipe(tubofd);
  if (tubo==-1) {
    perror("CREAZIONE PIPE FALLITA\n");
    exit(EXIT_FAILURE);
  }
  pid_t child=fork();
  if (child<0) {
    perror("FORK FALLITA\n");
    exit(EXIT_FAILURE);
  }
  if (child==0) {                                 //CODICE PROCESSO FIGLIO
    close(tubofd[1]);                             //l'estremità "scrittura" è inutile
    while (read(tubofd[0], &buffer, 1)>0) {       //legge 1 byte per volta finché il file non finisce
      write(STDOUT_FILENO, &buffer, 1);           //anche l'utente leggerà quello che il figlio starà leggendo
    }
    write(STDOUT_FILENO, "\n", 1);
    close(tubofd[0]);
    exit(EXIT_SUCCESS);
  }
  else {                                          //CODICE PROCESSO PADRE
    close(tubofd[0]);
    write(tubofd[1], argv[1], strlen(argv[1]));
    close(tubofd[1]);
    wait(NULL);                                   //IMPORTANTE: aspetta il figliolo
    exit(EXIT_SUCCESS);
  }
  return 0;
}
