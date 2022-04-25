#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
    Quarto exemplo de uso da funcao fork()
    - Invocacoes sucessivas a funcao fork() para criacao de 3 processos
    - processos dormem por 15s
    - so o processo original se clona, controlando o numero
    de processos gerados
*/

int main(void)
{
    char c;

    int fork_return;
    printf("Mensagem antes do fork()\n");
    printf("Aperte <ENTER> para clonar este processo: ");
    scanf("%c", &c);

    fork_return = fork();

    if (fork_return > 0)
    {
        printf("Mensagem antes do 2o fork()\n");
        printf("Aperte <ENTER> para clonar este processo novamente: ");
        scanf("%c", &c);
        //processo original
        fork();
    }

    printf("Mensagem depois do fork()\n");
    sleep(15);
    printf("Processo finalizando... meu PID era: %d\n", getpid());
    return 0;
}