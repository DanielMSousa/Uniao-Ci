#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signal.h>

int main(void)
{
    //int kill(pid_t pid, int sig)

    int fork_return;

    printf("[ORIGINAL] Sou o processo original, PID: %d\n", getpid());

    fork_return = fork();

    if (fork_return == 0)
    {
        //clonado
        printf("[CLONADO] Sou o processo clonado, PID: %d\n", getpid());
        printf("Dormindo 30s..\n");
        sleep(30);
    }
    else
    {
        char c;
        int kill_return;
        //original
        printf("[ORIGINAL] Vou finalizar o processo clonado\n");
        printf("[ORIGINAL] PID do processo clonado: %d\n", fork_return);
        printf("Aperte <ENTER> para finalizar o processo clonado: ");
        scanf("%c", &c);
        kill_return = kill(fork_return, SIGHUP);
        if (!kill_return)
            printf("[ORIGINAL] Kill realizado com sucesso! PID %d\n",
                   fork_return);
        printf("[ORIGINAL] Vou dormir 10s...\n");
        sleep(10);
    }

    return 0;
}