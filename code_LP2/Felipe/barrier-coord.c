#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_THREADS 5

int arrive[NUMBER_THREADS] = { 0 };
int proceed[NUMBER_THREADS] = { 0 };

void *worker (void *p)
{
	long i = (long) p;
	int sleep_time = i +1;

	while (1) {
		printf("[%ld] sleep = %d\n..\n", i, sleep_time);
		
		sleep(sleep_time);

		printf("[%ld] task done\n..\n", i);

		arrive[i] = 1;

		while (proceed[i] != 1);

		proceed[i] = 0;

		printf("[%ld] Saindo da barreira\n..\n", i);
	}

	return p;
}

void *coordinator (void *p)
{
	while (1) {
		for (int i = 0; i < NUMBER_THREADS; ++i) {
			while (arrive[i] != 1);
			arrive[i] = 0;
		}
	
		for (int i = 0; i < NUMBER_THREADS; ++i) {
			proceed[i] = 1;
		}
	}

	return p;
}

int main (void)
{
	pthread_t threads[NUMBER_THREADS];
	pthread_t t_coord;

	if (pthread_create(&t_coord, NULL, coordinator, NULL) != 0) {
		// handle error
	}

	for (int i = 0; i < NUMBER_THREADS; ++i) {
		long arg = (long) i;

		if (pthread_create(&threads[i], NULL, worker, (void *) arg) != 0) {
			// handle error
		}
	}

	sleep(20);

	exit(EXIT_SUCCESS);
}
