#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int pid_to_kill;
    int kill_return;
    int valor_op;

    printf("Digite a operaçao que deseja\n(1 - finalizar processo)\n(0 - sair)\n");
    scanf("%d", &valor_op);

    while (valor_op == 1)
    {
        kill_return = kill(pid_to_kill, SIGKILL);

        printf("Digite o PID do processo que deseja finalizar: ");
        scanf("%d", &pid_to_kill);

        if (!kill_return) // se o kill_return não for encontrado
        {
            printf("Processo com PID %d finalizado com sucesso\n", pid_to_kill);
        }
        else
        {
            printf("Nao foi possivel finalizar o processo com PID %d\n", pid_to_kill);
        }
    }

    return 0;
}