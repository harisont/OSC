#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define N 1000

int main(int argc, char const *argv[]) {
  int file= open(argv[1], O_RDWR | O_CREAT);        /*O_RDWR specifica che il file è aperto in lettura e scrittura,
                                                      O_CREAT che il file viene creato se non preesiste. Il valore
                                                      restituito da open() è un descrittore intero del file*/
  if (file==-1) perror("Creazione file fallita");
  else {
    char charbuf[1]="a";
    for (int i=1; i<=N; i++) {
      int w= write(file, charbuf, 1);               //viene scritto un byte per volta (III parametro di write())
      if (w==-1) perror("Scrittura fallita.");
    }
    close(file);
  }
  return 0;
}
