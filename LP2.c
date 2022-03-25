#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

    int nprocessos, x, y = 1;
    printf("Digite a quantidade de processos: ");
    scanf("%d",&nprocessos);
    if(nprocessos > 1){
        x = fork();
        for(int i = 0; i < nprocessos - 2; i++){
            if(x > 0){
                x = fork();
            }
        }
        
    }else if(nprocessos <= 0){
        printf("Entrada inválida! Número deve ser > 0\n");
        return -1;
    }
    printf("Saida\n");
    return 0;
}