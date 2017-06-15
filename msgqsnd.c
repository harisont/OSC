#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct message {
  long msgtype;   //verrà utilizzato nella ricezione del messaggio, deve essere positivo
  char msgtxt[500];   //la max lunghezza del messaggio sarà di 500 char
};

int main(int argc, char const *argv[]) {
  struct message buffer;
  int msgq;
  if(msgq=msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL)==-1) {  //crea una nuova coda di messaggi
    if(errno==EEXIST) perror("Errore: coda preesistente");
    else perror("Errore non identificato nella creazione della coda");
  }
  puts("\nTesto del messaggio:");
  buffer.msgtype=1;   //viene impostato un tipo di messaggio qualsiasi
  while(fgets(buffer.msgtxt, sizeof(buffer.msgtxt), stdin)!=NULL) {     //l'utente inserisce il messaggio
    int length=strlen(buffer.msgtxt);
    if (buffer.msgtxt[length-1] == '\n') buffer.msgtxt[length-1] = '\0';    //scrive EOF
    if(msgsnd(msgq, &buffer, length+1, 0)==-1) perror("Invio messaggio fallito");    //invia il messaggio
  }
  if(msgctl(msgq, IPC_RMID, NULL)==-1) perror("Chiusura coda di messaggi fallita");  //chiude la coda di messaggi, come specificato da IPC_RMID
}
