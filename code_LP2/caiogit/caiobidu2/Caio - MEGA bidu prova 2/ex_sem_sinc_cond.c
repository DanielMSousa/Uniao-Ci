#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>

sem_t arrive1, arrive2, arrive3;

void* worker1(void* p) {
	printf("[1] Iniciando job\n");
	sleep(6);
	printf("[1] Finalizando job\n");
	sem_post(&arrive1);
	sem_wait(&arrive2);
	sem_wait(&arrive3);
	printf("[1] Passei do ponto de barreira\n");
}

void* worker2(void* p) {
	printf("[2] Iniciando job\n");
	sleep(3);
	printf("[2] Finalizando job\n");
	sem_post(&arrive2);
	sem_wait(&arrive1);
	sem_wait(&arrive3);
	printf("[2] Passei do ponto de barreira\n");
}

void* worker3(void* p) {
	printf("[3] Iniciando job\n");
	sleep(9);
	printf("[3] Finalizando job\n");
	sem_post(&arrive3);
	sem_wait(&arrive1);
	sem_wait(&arrive2);
	printf("[3] Passei do ponto de barreira\n");

}

int main(void) {
	pthread_t w1, w2, w3;

	sem_init(&arrive1, 0, 0);
	sem_init(&arrive2, 0, 0);
	sem_init(&arrive3, 0, 0);

	pthread_create(&w1, 0, worker1, 0);
	pthread_create(&w2, 0, worker2, 0);
	pthread_create(&w3, 0, worker3, 0);

	pthread_join(w1, 0);
	pthread_join(w2, 0);
	pthread_join(w3, 0);

	sem_destroy(&arrive1);
	sem_destroy(&arrive2);
	sem_destroy(&arrive3);

	return 0;
}
