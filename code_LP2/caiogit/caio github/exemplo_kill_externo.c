#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

    int pid_to_kill;
    int kill_return;

    printf("Digite o PID do processo que deseja finalizar: ");
    scanf("%d", &pid_to_kill);

    kill_return = kill(pid_to_kill, SIGKILL);

    if (!kill_return)
    {
        printf("Processo com PID %d finalizado com sucesso\n",
               pid_to_kill);
    }
    else
    {
        printf("Nao foi possivel finalizar o processo com PID %d\n",
               pid_to_kill);
    }

    return 0;
}