#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define QUANTIDADE_LISTA 5
#define TAM_STR 8
#define STR_TESTE "AAAAAAA"

int main(void)
{
    int i;
    int fork_return;

    char *tmp[] = {"abc", "def", "xyz", NULL};
    char *lista[QUANTIDADE_LISTA + 1];

    for (i = 0; i < QUANTIDADE_LISTA; i++)
    {
        lista[i] = (char *)malloc(sizeof(char) * TAM_STR);
        strcpy(lista[i], STR_TESTE);
    }

    lista[i] = NULL;

    fork_return = fork();

    if (fork_return == 0)
    {
        //processo clonado
        printf("[PEE] primeira execucao: \n");
        sleep(20);
        execl("mostra", "ABC", "XYZ", (char *)NULL);
    }
    else
    {
        //processo original
        fork_return = fork();
        if (fork_return == 0)
        {
            //processo clonado do original 2
            printf("[PEE] segunda execucao: \n");
            sleep(20);
            execv("mostra", lista);
        }
        else
        {
            //processo original
            fork_return = fork();
            if (fork_return == 0)
            {
                //processo clonado do original 3
                printf("[PEE] terceira execucao: \n");
                sleep(20);
                execve("mostra", tmp, NULL);
            }
        }
    }

    sleep(20);

    return 0;
}