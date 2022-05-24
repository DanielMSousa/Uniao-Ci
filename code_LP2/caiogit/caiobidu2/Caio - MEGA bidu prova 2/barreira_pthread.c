#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define QTD_THREADS 5
#define LIMITE_CONJ_JOBS 3

pthread_barrier_t barreira;
int contador_conj_jobs = 0;

void* worker(void* p) {
	while (contador_conj_jobs < LIMITE_CONJ_JOBS) {
		long idx = (long)p;
		int sleep_time = rand() % 8;
		printf("[%ld] Job: %d\n", idx, sleep_time+1);
		sleep(sleep_time+1);
		//sleep(1+idx);
		printf("[%ld] Terminei o job\n", idx);
		pthread_barrier_wait(&barreira);
		printf("[%ld] Passei da barreira\n", idx);
		fflush(stdout);
	}

}

int main(void) {
	time_t t;
	pthread_t threads[QTD_THREADS];

	srand(time(&t));

	pthread_barrier_init(&barreira, NULL, QTD_THREADS + 1);

	for (long i = 0; i < QTD_THREADS; i++)
		pthread_create(&threads[i], NULL, worker, (void*)i);


	while (contador_conj_jobs < LIMITE_CONJ_JOBS) {
		printf("[main] Conjunto: %d\n", contador_conj_jobs);
		pthread_barrier_wait(&barreira);
		__sync_fetch_and_add(&contador_conj_jobs, 1);

	}

/*
	for (int i = 0; i < QTD_THREADS; i++)
		pthread_join(threads[i], NULL);
*/
	int ret = pthread_barrier_destroy(&barreira);

	printf("[main] BARRIER DESTROY: %d\n", ret);

	return 0;
}
