#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    clock_t t_p1, t_p2, t_p; // dá um tipo específico para a variável t_p
    int pid_original;        // dá um valor inteiro para a variável pid_original

    pid_original = getpid(); // a variável irá iniciar a função getpid, que retornará o pid do processo
    t_p1 = clock();          // t_p iniciará a função clock, que retornará o tempo atual

    for (int i = 0; i < 30; i++) //
    {
        if (pid_original == getpid())
        {
            fork();
        }

        if (pid_original != getpid())
        {
            sleep(2);
        }

        
    }
    if (pid_original == getpid())
        {
            t_p2 = clock();
            t_p = t_p2 - t_p1;
            printf("Tempo de execução: %.2lf ms\n", ((double)t_p)/((CLOCKS_PER_SEC/1000)));
        }

    return 0;
}