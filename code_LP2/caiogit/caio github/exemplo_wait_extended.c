#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

/*
    Processo original gera mais dois processos, e estes dormem um
    tempo aleatorio; o processo original aguarda o primeiro ser 
    finalizado e exibe informacoes capturadas atraves da funcao 
    wait()

    Versao simplificada do waitpid, o unico parametro eh o ponteiro que vai pegar o exit do primeiro processo q terminar.
    Aqui você nao seleciona o processo que está esperando como no waitpid

    Lembrando sempre do WEXITSTATUS( ) porque so assim o exit é printado corretamente

*/

int main(void)
{
    char c;

    int fork_return; // return 1
    int fork_return2; // return 2

    printf("[O] Vou pegar o exit do valor que sair primeiro com a funcao wait\n");
    printf("[O] Aperte <ENTER> para criar 2 processos: ");
   
    scanf("%c", &c);

    fork_return = fork(); // original > 0, clone = 0; 
    // pid clone = fork_return do original, pid original = pid clone -1

    if (fork_return > 0) // ou seja, o original
    {
    
        fork_return2 = fork(); // original se clonou de novo num clone2
        if (fork_return2 > 0) // dentro do original
        {
            //processo original
            int exit_value, wait_value;
           
            wait_value = wait(&exit_value); // waitvalue pega o pid do que ele esperou

            printf("[O] Valor de saida do que acabou primeiro: %d\n",
                   WEXITSTATUS(exit_value));

            printf("[O] PID do processo que eu esperei: %d\n",
                   wait_value);
        }
        else // o clone2
        {
            //segundo processo clonado
            printf("[2C] Sou o processo 2C, PID %d e exit 22\n", getpid());
            srand(getpid());
            int dormir = rand() % 20;
            printf("[2C] Vou dormir %d s e sair...\n", dormir);
            sleep(dormir);
            exit(22);
        }
    }
    else
    {
        // primeiro processo clonado
        //segundo processo clonado
        printf("[1C] Sou o processo 1C, PID %d e exit 11\n", getpid());
        srand(getpid());
        int dormir = rand() % 20;
        printf("[1C] Vou dormir %d s e sair...\n", dormir);
        sleep(dormir);
        exit(11);
    }

    printf("Processo original finalizando... meu PID era: %d\n", getpid());
    return 0;
}