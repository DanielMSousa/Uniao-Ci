#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>

/*
Wait funciona da seguinte forma, o primeiro parametro é o pid que se deseja esperar, o segundo que 
é um ponteiro de inteiro serve para se armazenar o valor exit do processo quando ela encerrar
e para acessar esse conteudo precisa usar WEXITSTATUS(ponteiro)

*/
int main(void) {

int forkreturn;
int prowait;
int origemwait;

    forkreturn = fork();

    if(forkreturn>0) {

        printf("[O] ola, nao sei bem o que estou fazendo mas sou o processo original e vou esperar\n");
         origemwait = waitpid(forkreturn, &prowait, 0);
        printf("[O] meu pid eh igual a: %d\n", getpid());
        printf("[O] o valor que a variavel forkreturn esta agora eh: %d\n", forkreturn);
        printf("so pra saber, origemwait eh: %d e prowait eh: %d\n", origemwait, prowait);
         printf("so pra saber, origemwait eh: %d e prowait eh: %d\n", origemwait, &prowait);
        printf("Para aparecer o valor que coloquei no exit: %d\n",
         WEXITSTATUS(prowait));
         printf("\no pid com %d tem como exit o valor %d\n", origemwait, WEXITSTATUS(prowait));
         printf("\nADEUS \n");
       

    } 
    if(forkreturn == 0) { 
        printf("[C] ola, sou o processo clone e meu pid eh: %d\n", getpid());
        printf("[C] o valor de forkreturn agora eh de: %d\n", forkreturn);
        printf("[C] Tenho todo tempo do mundo pra fazer o que eu quiser entao vou dormir muito aqui\n");
        sleep(2);
        printf(" boa noite...\n");
        sleep(2);
        printf(" zzzzzzz....\n");
        sleep(2);
        printf(" zzzzzzzzzzzzzzzz....\n");
        sleep(2);
        printf("\n Bom diaaaa....\n");
        sleep(2);
        printf(" Agora quero encerrar, adeus!!\n\n");
        //origemwait = waitpid(544, &prowait, 0);
        exit(16);


    }





    return 0;
}