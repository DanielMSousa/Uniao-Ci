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
    printf("Entrou Thread\n");
    sleep(2);
    printf("Saindo Thread >>>\n");
}


int main(void){
    pthread_t thread;
    clock_t t, p;
    int r;
    t = clock();//armazena tempo inicial
    p = clock();//armazena tempo inicial
    pthread_create(&thread, NULL, functionThread, NULL);//cria thread
    pthread_join(thread, NULL);//retorna para main
    t = clock() - t;//Calcula tempo da thread
    printf("Tempo execução thread: %ld\n", t);
    r = fork();//bifurca em dois processos
    if(r > 0){
        functionProcess(); //executa em um dos processos a função 2 segundos
        p = clock() - p;//calcula tempo que o processo termina
        printf("Time processo: %ld\n", p);
    }
    
    return 0;
}
