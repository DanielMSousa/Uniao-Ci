#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <time.h>
#define QTDTHREADS 5
#define QTDGENERATE 10
#define BUFFER_SIZE 8

int buf[BUFFER_SIZE];

int front = 0, rear = 0; 

sem_t empty, full; // EMPTY E FULL NUNCA TEM O MSM VALOR

void* prod(void* p) {
    int valor_prod;
    int count = 0;

    while(count < QTDTHREADS) {

        sem_wait (&empty);
        valor_prod = rand() % 255;
        printf("[prod] %d \n", valor_prod);
        buf[rear] = valor_prod;
        rear = (rear+1) % BUFFER_SIZE;
        sleep(2);
        sem_post(&full);
        count++;

    }

}

void* cons(void* p) {
 int valor_cons;
 int count = 0;

    while(count <QTDGENERATE) {

        sem_wait(&full);
        valor_cons = buf[front];
        front = (front+1) % BUFFER_SIZE;
        printf("[cons] %d \n", valor_cons);
        sleep(2);
        sem_post(&empty);
        count++;




    }
 
}

int main(void) {

pthread_t _prod, _cons;
time_t t;

for (int i=0; i <BUFFER_SIZE; i++)
buf[i] = 0;

srand(time(&t));

sem_init (&empty, 0, BUFFER_SIZE);
sem_init (&full, 0, 0);

pthread_create(&_prod, NULL ,prod, NULL);
pthread_create(&_cons, NULL ,cons, NULL);

pthread_join(_prod, NULL);
pthread_join(_cons, NULL);

// codigo de 1 pra 1, a tarefa eh generalizar de n para m;

sem_destroy(&empty);
sem_destroy(&full);

return 0;
}


