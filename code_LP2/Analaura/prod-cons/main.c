#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define QTD_JORNAIS 2
#define QTD_ESCRITORES 2
#define BUFFER_SIZE 4

pthread_t thread_jornal[QTD_JORNAIS];
pthread_t thread_escritores[QTD_ESCRITORES];
pthread_mutex_t buffer_use;
sem_t buffer_full, buffer_empty;
char buffer;
int currentIdx = 1;

void* escritor(void* p) {
    long id = (long) p;
    char letra;
    while (1)
    {
            letra = (rand() % (122 - 97 + 1)) + 97;
            sem_wait(&buffer_full);
            pthread_mutex_lock(&buffer_use);
            buffer = letra;
            pthread_mutex_unlock(&buffer_use);
            sem_post(&buffer_empty);
            sleep(1);
    }
}
  
void* jornal(void* p){
    long id = (long) p;
    int letra;
    while (1)
    {    sem_wait(&buffer_empty);
         pthread_mutex_lock(&buffer_use);
         letra = buffer;
         pthread_mutex_unlock(&buffer_use);
         sem_post(&buffer_full);
         printf("Sou o jornal [%ld] --> esta é a mensagem que recebi %c\n", id, letra);
         sleep(1);
    }
    
   
}


int main(void){

    sem_init(&buffer_empty, 0, 0);
    sem_init(&buffer_full, 0, BUFFER_SIZE);
    pthread_mutex_init(&buffer_use, NULL);
    // currentIdx = 0;
    for (long i = 0; i < QTD_ESCRITORES; i++)
    {
        pthread_create(&thread_escritores[i], NULL, escritor, (void*)i);
    }
     for (long l = 0; l < QTD_JORNAIS; l++)
    {
        pthread_create(&thread_jornal[l], NULL, jornal, (void*)l);
    }
    for (long j = 0; j < QTD_ESCRITORES; j++)
    {
        pthread_join(thread_escritores[j], NULL);
    }
     for (long k = 0; k < QTD_JORNAIS; k++)
    {
        pthread_join(thread_jornal[k], NULL);
    }
    sem_destroy(&buffer_empty);
    sem_destroy(&buffer_full);
    pthread_mutex_destroy(&buffer_use);
    return 0;
}