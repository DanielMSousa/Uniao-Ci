#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
    Primeiro exemplo de uso da funcao fork()
    - Clona o processo e tanto o original quanto o clonado 
    dormem por 20s (e exibem as mesmas mensagens duplicadas)
*/

int main(void)
{
    char c;
    printf("Programa que se clonara\n");
    printf("Aperte qualquer tecla para clonar esta execucao: ");
    scanf("%c", &c); //bloqueia ate usuario inserir valor
    fork();          //clona processo em execucao
    /* mensagens abaixo aparecerao duplicadas na execucao */

    printf("Mensagem apos  o fork (clonagem)!\n");
    printf("Dormirei por 20s...\n\n");
    sleep(20); // verificar (ps/top/gerenciador de tarefas)
               // a existencia do processo clonado

    printf("Finalizando as duas instancias, pid desta: %d\n", getpid());

    return 0;
}