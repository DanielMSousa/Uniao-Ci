// 1) Faça um programa em C/C++ em que você compare o tempo de criação de 30 
// threads e 30 processos, onde as threads e processos criadas apenas executem
// uma função que exiba uma mensagem ("Nova thread" ou "Novo processo") e as faça
// dormir por 2s. Use alguma função de medição de tempo* para tal e escreva suas
// impressões sobre o resultado, respondendo qual das opções demandou menos tempo
// de execução para ser realizada e faça a relação disso com consumo de 
// processamento e memória. Para finalizar, faça uma clara distinção (em 
// comentários no código) das diferenças principais entre threads e processos.
//  Ao término do programa, nenhum processo deverá permanecer em execução.

// * Funções sugeridas para uso no processo de medição de tempo de execução são 
// listadas abaixo. 
// - Em C/C++: time(),  clock(), clock_gettime() (biblioteca time.h), 
//   gettimeofday() (biblioteca sys/time.h);
// - Em C++: método chrono::high_resolution_clock (biblioteca chrono). 
// - Sugestão de referência: https://tinyurl.com/medirtempoemc
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void functionProcess(){
    printf("Funçao clonada com fork()\n");
    sleep(2);
    printf("Saindo fork >>>\n");
} 
void* functionThread(){
    // printf("Entrou Thread\n");
    // printf("Saindo Thread >>>\n");
}


int main(void){
    pthread_t thread[30];
    clock_t t, p, f, pp, tp, pf;
    int n, fork_return, pid_original;
    int r;
    //armazena tempo inicial
    //armazena tempo inicial
    p = clock();
    for(int i = 0; i < 30; i++){
        
        pthread_create(&thread[i], NULL, functionThread, NULL);//cria thread
        
    }
    t = clock();
    f = t - p;//Calcula tempo da thread
    //pthread_join(thread[i], NULL);//retorna para main
   
    printf("Tempo execução thread: %lf ms\n", (double)f/(CLOCKS_PER_SEC/1000));
    //bifurca em dois processos
    pid_original = getpid(); 
    pp = clock();

    for (int i = 0; i < 30; i++) {
        if (pid_original == getpid()) { 
            //processo original
            fork();

        }
    }

    if(pid_original == getpid()){
        tp = clock();
        pf = tp - pp;
        printf("Tempo execução processo: %lf ms\n", (double)pf/(CLOCKS_PER_SEC/1000));
    }
    



    return 0;
}