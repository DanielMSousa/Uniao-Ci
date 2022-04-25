#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#define int QTD_LETRAS;



void* gera_dicionario_thread(*void p){
    return 0;
}
int gera_dicionario_proc(char c){
    return 0;
}
int main(){ 

    char opcao;
    pthread_t threads[QTD_LETRAS];
    //int child_pids[QTD_LETRAS];
    opcao = 't';
    if(opcao == 't'){
        for(long i = 0; i < QTD_LETRAS; i++){
            pthread_create(&threads[i], NULL, gera_dicionario_thread, (void*)i);
        }
        for(int i = 0; i < QTD_LETRAS; i++){

            //segundo parametro é o retorno da thread
            pthread_join(threads[i], NULL);
        }
        char letra = 'A';

        for(int j = 0; j < QTD_LETRAS; j++){
            char filename[10];
            sprintf(filename, "%c.text", letra + j);
            FILE* textfile;
            FILE* dicfile;
            textfile = fopen(filename, "r");
            dicfile = fopen(filename, "w");
        }

    }else if(opcao == 'p'){
        int fork_return;
        fork_return = fork();
        if(fork_return == 0){
            gera_dicionario_proc();
        }else{
            
        }

    }else{
        printf("Opcao inválida\n");
    }

}
