#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define QTDTHREADS 2


int var = 0;
int boolean = 0;

void* secao(void* p) {
    long i = (long)p;
    while(1) {
        //while(booleao);
        while (__sync_lock_test_and_set(&boolean, 1)); 
        //while(booleao);
        var += 10;
        printf("[%ld] thread na situacao critica [%d]\n", i, var);
        puts(..);
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
    printf("var igual a %d", var);
    return 0;
}