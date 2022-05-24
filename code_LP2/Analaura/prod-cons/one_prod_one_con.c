#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 1000

pthread_t thread_jornal;
pthread_t thread_escritores;
sem_t buffer_full, buffer_empty;
char buffer;

void* escritor(void* p) {
    long id = (long) p;
    char letra;
    while (1)
    {
            letra = (rand() % (122 - 97 + 1)) + 97;
            sem_wait(&buffer_full);
            buffer = letra;
            sem_post(&buffer_empty);
            sleep(1);
    }
}
  
void* jornal(void* p){
    long id = (long) p;
    char letra;
    while (1)
    {    sem_wait(&buffer_empty);
         letra = buffer;
         sem_post(&buffer_full);
         printf("Sou o jornal [%ld] --> esta é a mensagem que recebi %c\n", id, letra);
         sleep(1);
    }
    
   
}


int main(void){
    sem_init(&buffer_empty, 0, 0);
    sem_init(&buffer_full, 0, BUFFER_SIZE);

    pthread_create(&thread_escritores, NULL, escritor, (void*)0);

    pthread_create(&thread_jornal, NULL, jornal, (void*)0);

    pthread_join(thread_escritores, NULL);

    pthread_join(thread_jornal, NULL);

    sem_destroy(&buffer_empty);
    sem_destroy(&buffer_full);
    return 0;
}