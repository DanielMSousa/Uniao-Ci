#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define QTDTHREADS 5

int number = 0; // pega o numero pra proxima vez que ela vai passar
int next = 0; // incrementa 1 por 1 apos cada thread passar, diz a vez de quem eh
int turn[QTDTHREADS] = {0 , 0, 0, 0, 0}; // aqui eh onde cada thread vai segurar seu ticket

int var_global = 0; 


void* seccrit(void* p) {

    long id = (long)p; // indice
    printf("voce criou uma thread de id: %ld\n", id);
    while(1){
    turn[id] = __sync_fetch_and_add(&number,  1); // vai colocar o valor do number pra proxima vez q ela passar
    while(turn[id] != next) ;
    var_global++;
    printf("id: %ld var: %d number: %d turn: %d, next: %d \n", id, var_global, number, turn[id], next);
    sleep(1);
    next++;
    }


}

int main(void) {
	pthread_t threads[QTDTHREADS];
    printf("sou a main\n");
    for( long i = 0; i<QTDTHREADS; i++) {

    pthread_create(&threads[i], NULL, seccrit, (void*)i);

    }
	
	
	
	sleep(35);
	return 0;
}
