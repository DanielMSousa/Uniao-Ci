#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_THREADS 5

int count = 0;

void *worker (void *p)
{

	long i = (long) p;
	int sleep_time = i +1;

	while (1) {
		printf("[%ld] task = sleep %d ; count = %d\n", i, sleep_time, count);
		printf("..\n");

		// task i
		sleep(sleep_time);

		printf("[%ld] Task done\n..\n", i);

		__sync_fetch_and_add(&count, 1);
	
		while ((count % NUMBER_THREADS) != 0);

		printf("[%ld] Saindo da barreira\n..\n", i);
	}
}

int main (void)
{
	pthread_t threads[NUMBER_THREADS];

	for (int i = 0; i < NUMBER_THREADS; ++i) {
		long arg = i;

		if (pthread_create(&threads[i], NULL, worker, (void *) arg) != 0) {
			// handle error
		}
	}	

	sleep(20);

	exit(EXIT_SUCCESS);	
}
