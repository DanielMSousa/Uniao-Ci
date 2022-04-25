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
    char *tmp[] = {"abc", "def", "xyz", NULL};
    char *lista[QUANTIDADE_LISTA + 1];

    for (i = 0; i < QUANTIDADE_LISTA; i++)
    {
        lista[i] = (char *)malloc(sizeof(char) * TAM_STR);
        strcpy(lista[i], STR_TESTE);
    }

    lista[i] = NULL;
    /*
    printf("[PEE] primeira execucao: \n");
    execl("mostra", "ABC", "XYZ", (char *)NULL);
*/
    printf("[PEE] segunda execucao: \n");
    execv("mostra", lista);

    return 0;
}