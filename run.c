#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  if(strcmp("ls", argv[1])==0) {
    execl("/bin/ls", "ls", NULL);
    perror("Error!");
  }
  else if(strcmp("pwd", argv[1])==0){
    execl("/bin/pwd", "pwd", NULL);
    perror("Error!");
  }
  //è possibile aggiungere altri comandi da eseguire seguendo la sintassi del precedente else if
  else puts("Unknown command.");
}
