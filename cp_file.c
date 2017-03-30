#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

/*Questo programma esegue la copia di un file senza passare per i buffer, mappando i file direttamente nello spazio di
memoria riservato al processo.*/


int main(int argc, char const *argv[]) {
  int in, out;                                          //variabili che conterranno i descrittori dei file
  if (argc != 3) {
    fprintf(stderr, "Per utilizzare il programma, digitare il nome dell'eseguibile seguito dal nome del file di input e quello del file di output.\n");
    exit (1);
  }
  in= open(argv[1], O_RDONLY);                          //il file di input viene aperto in sola lettura
  if (in==-1) {
    perror("APERTURA FILE INPUT FALLITA\n");
    exit(2);
  }
  out= open(argv[2], O_RDWR | O_CREAT);
  if (out==-1) {
    close(in);
    perror("APERTURA FILE OUTPUT FALLITA\n");
    exit(2);
  }
  size_t size = lseek(in, 0, SEEK_END);                 /*size_t, definito in <sys/types.h>, è in pratica un int. lseek()
                                                          imposta l'offset, cioè la posizione corrente sul file aperto
                                                          (f_pos), secondo la specifica SEEK_END, ossia alla fine del
                                                          file. Il secondo parametro (off_t offset) è il punto nel file
                                                          da cui inizia la mappatura. In pratica calcola la dimensione
                                                          del file di input.*/
  lseek(out, size - 1, SEEK_SET);                       //imposta la posizione corrente all'ultima del file di output
  char end='\0';
  write(out, &end, 1);                                  /*scrive il carattere di terminazione nell'ultima posizione
                                                          del file di output*/
  void *source, *target;
  source=mmap(0, size, PROT_READ, MAP_SHARED, in, 0);   /*MAPPATURA FILE DI INPUT:
                                                          i parametri di mmap() sono: void* address= indirizzo inizio
                                                          mappatura; size_t length= numero byte da mappare; int
                                                          protection= permessi; int flags: determina la visibilità
                                                          delle modifiche ai dati mappati; int filedes= descrittore
                                                          del file da mappare; off_t offset= punto d'inizio mappatura*/
  if (source==MAP_FAILED) {
    perror("ERRORE DURANTE IL MAPPING DEL FILE DI INPUT\n");
    exit (1);
  }

  target=mmap(0, size, PROT_READ, MAP_SHARED, out, 0);  /*MAPPATURA FILE DI OUTPUT*/
  if (target==MAP_FAILED) {
    perror("ERRORE DURANTE IL MAPPING DEL FILE DI OUTPUT\n");
    exit (2);
  }

  memcpy(target, source, size);                         /*copia il file di input nel file di output. Con memcpy() le
                                                          rispettive zone di memoria non devono sovrapporsi*/
  munmap(source, size);                                 //eliminazione mappatura file di input
  munmap(target, size);                                 //eliminazione mappatura file di output
  close(in);
  close(out);
  exit(0);

  return 0;
}
