#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pid_to_wait;
    int pid_exit_value;
    int wait_return_value;

    pid_to_wait = fork();

    if (pid_to_wait > 0)
    {

        //processo original

        printf("[O] Aguardando termino do processo com PID %d\n",
               pid_to_wait);

        wait_return_value = waitpid(pid_to_wait, &pid_exit_value, 0);

        printf("[O] Valor de retorno do processo aguardado: %d\n",
               WEXITSTATUS(pid_exit_value));

        printf("[O] Valor de retorno do wait: %d\n", wait_return_value);
    }
    else
    {

        //processo clonado
        printf("[C] Vou dormir 20s...\n");
        sleep(20);
        exit(66);
    }

    return 0;
}