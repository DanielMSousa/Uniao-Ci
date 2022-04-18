#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>

/*
Waitpid funciona da seguinte forma, o primeiro parametro é o pid do processo que vamos esperar, o segundo
é um ponteiro de inteiro que armaza o valor exit desse processo que escolhemos esperar.
OBS: para acessar o conteudo do segundo parametro precisa usar WEXITSTATUS(nome do segundo parametro).
OBS2: waitpid retorna o pid do processo que foi esperado (colocado na frente da fila);
*/

int main(void) {

int forkreturn;
int prowait;
int origemwait;

    forkreturn = fork();

    if(forkreturn > 0) {
        printf("[O] Ola, sou o processo original e meu pid eh: %d, agora vou esperar pelo clone...\n", getpid());
            origemwait = waitpid(forkreturn, &prowait, 0);
        printf("[O] O valor de forkreturn no processo original: %d\n", forkreturn);
        printf("[O] O valor de origemwait eh: %d\n", origemwait);
        printf("[O] O valor recebido por exit usando WEXITSTATUS(prowait): %d\n", WEXITSTATUS(prowait));
        printf("\n[O] O processo com pid %d tem como exit o valor %d\n", origemwait, WEXITSTATUS(prowait));
        printf("\n[O]FINALIZANDO \n");
    } 

    if(forkreturn == 0) { 
        printf("\n\n[C] Ola, sou o processo clone e meu pid eh: %d\n", getpid());
        printf("[C] O valor de forkreturn no processo clone eh: %d\n", forkreturn);
        printf("[C] Tenho todo tempo do mundo, entao vou dormir 10s\n\n");
        sleep(10);

        exit(12);

    }





    return 0;
}