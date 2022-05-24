#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define QTDTHREADS 3


int var;
int boolean;

void* secao(void* p) {
    long i = (long)p;
    while(1) {
        while (boolean == 1){ } 
        boolean = 1;
        printf("[%ld] thread na situacao critica\n", i);
        var += 10;
        sleep(3);
        printf("[%ld] vou abrir os portoes\n", i);
        boolean = 0; 
        printf("[%ld] quem quiser passar vai simbora\n", i);
        sleep(1);

    }

}

int main(void) {
    boolean = 0;
    var = 10;
    pthread_t se[QTDTHREADS];

    for (long i = 0; i< QTDTHREADS; i++) {

        pthread_create(&se[i], NULL, secao, (void*)i);
    }


 
    sleep(24);
    return 0;
}