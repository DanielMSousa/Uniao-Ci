// 5) Faça um programa em C/C++ onde são criadas 2 threads: 
// uma thread produtora, e a outra consumidora. A thread produtora deverá gerar 
// 100 valores inteiros aleatórios entre 0 e 255 e armazenar em um array compartilhado 
// com 10 posições. A thread consumidora buscará as informações no array e exibi-los, de 
// forma que nenhum valor seja perdido. Use semáforos implementando a solução do buffer 
//compartilhado. 


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
int buffer[10];

sem_t ready, printed;
pthread_mutex_t in_use;

void* produtor(void* p){
    int value, j;
    j = 10;
    while (j > 0)
    {

        sem_wait(&printed);

            for (int i = 0; i < 10; i++)
        {
            value = rand() % 255;
            printf("***Sou o produtor e estou colocando %d na posição buffer %d***\n", value, i);
            buffer[i] = value;
            // sleep(1);
        }
  
        sem_post(&ready);
        j--;
    }
    
    
    

}
void* consumidor(void* p){
    int j = 10;
    while (j > 0)
    {

        sem_wait(&ready);

        // sem_post(&printed);
        for (int i = 0; i < 10; i++)
        {
            
            printf("buffer[%d]: %d\n", i, buffer[i]);
            sleep(1);
            
        }
        sem_post(&printed);
        j--;
    }
    
    
    
}

int main(void){
    pthread_t produtor_thread, consumidor_thread;
    sem_init(&ready, 0, 0);
    sem_init(&printed, 0, 1);

    pthread_create(&produtor_thread, NULL, produtor, NULL);
    pthread_create(&consumidor_thread, NULL, consumidor, NULL);
    pthread_join(produtor_thread, NULL);
    pthread_join(consumidor_thread, NULL);

    sem_destroy(&ready);
    sem_destroy(&printed);
}