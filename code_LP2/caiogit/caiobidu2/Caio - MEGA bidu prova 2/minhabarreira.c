#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define QTD_THREADS 5

int entrada[QTD_THREADS];
int saida[QTD_THREADS];

int arrive[QTD_THREADS];
int proceed[QTD_THREADS];

void* worker(void* p) {
	long id = (long)p;

	while(1) {
		printf("[%ld] iniciando tarefa...\n", id);
		saida[id] = 1 + rand() % 9;
		printf("[%ld] 1 entrada[id]: %d arrive[id]: %d proceed[id]: %d \n", id, entrada[id], arrive[id], proceed[id]);
		printf("[%ld] saida[id]: %d\n",id, saida[id]);
		sleep((int) (rand() % 3));
		printf("[%ld] Embarreirado, estou esperando\n", id);
		arrive[id] = 1;
		//printf("[%ld] 2 entrada[id]: %d arrive[id]: %d proceed[id]: %d \n", id, entrada[id], arrive[id], proceed[id]);
		while(proceed[id] != 1) usleep(30);
		proceed[id] = 0;
		//printf("[%ld] 3 entrada[id]: %d arrive[id]: %d proceed[id]: %d \n", id, entrada[id], arrive[id], proceed[id]);
	}


}

void* coord(void* p) {
	while(1) {

		for(int i = 0; i<	QTD_THREADS; i++) {

			while((arrive[i]) == 0) usleep(30);
			arrive[i] = 0;
		}
		printf("[COORD] Barreira cheia, liberando...\n");
		for(int i = 0; i< 	QTD_THREADS; i++) {

			proceed[i] = 1;
		}

	}
	return 0;
}

int main(void) {

pthread_t threads[QTD_THREADS];
pthread_t coorde;
time_t t;

srand((unsigned)time(&t) );

for(long i = 0; i < QTD_THREADS; i++) {

	pthread_create(&threads[i], NULL, worker, (void*)i);
}

	pthread_create(&coorde, NULL, coord, NULL);
	sleep(10);

	return 0;
}