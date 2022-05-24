#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define QTD_THREADS 5
int ticket[QTD_THREADS] = {0,0,0,0,0};
int global_vari = 0;
int number = 0;
int turno = 0;

void* thread_function(void* p){
    long idx = (long)p;

    while (1)
    {
        //ticket[0] = 1
        ticket[idx] = __sync_fetch_and_add(&number, 1);
        while (turno != ticket[idx]);
        global_vari++;
        printf("Global Vari thread[%ld] --> %d\n", idx,  global_vari);
        sleep(1);
        turno++;
    }
    
}

int main(void){
    pthread_t threads[QTD_THREADS];
    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }
    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}