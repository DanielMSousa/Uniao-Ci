// 2) Faça dois programas em C que solicitem uma string para o usuário (com até 8 
// caracteres). Os dois programas irão contar as ocorrências da string em um dos
// 6 arquivos anexados à esta lista utilizando concorrência - um deles usará 
// threads e o outro processos. Cada arquivo deverá ser processado por uma 
// thread/processo separado e no fim o programa deverá apresentar a soma das 
// ocorrências calculadas por cada processo antes de seu término. Comente o 
// código com as diferença do uso de threads e processos (do ponto de vista do
// programador). 

#include <stdio.h>
#include <string.h>
#include <unistd.h> 

void functionPrint(int indice){
    printf("Function here! (todo mundo)%d\n", indice);
}

int main(void){
            

        int numero = 6; 
        int processoPID;
        int nprocesso = 0;

        processoPID = getpid();
        functionPrint(nprocesso);
        nprocesso++;
        for (int i = 1; i <= numero - 1; i++)
        {
                
                if (processoPID == getpid())
                {
                        // Processo PAI
                        functionPrint(nprocesso);
                        fork();
                        nprocesso++;
                        
                }
                else
                {
                        
                }
        }
        
        
    return 0;
}