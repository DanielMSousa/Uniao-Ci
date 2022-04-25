#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(void) {

int fork_return, pidi, pidp;

pidi = getpid();
  fork_return = fork();
    
  printf("Se for > 0 sou o original: %d\n", fork_return);
    if(fork_return>0) {
        printf("[O] AAAAAHHH\n");
        pidp = getpid();

    } else {
        printf("[C] bbbbbbh\n");
        pidp = getpid();
    }
    printf("o pid original eh igual a pidi: %d\n", pidi);
    printf("Vou printar meu pid: %d \n", pidp);

  sleep(5);


return 0;  
}