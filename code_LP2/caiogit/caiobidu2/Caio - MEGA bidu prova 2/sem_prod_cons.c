#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define QTD_THREADS 5

int var_global = 0;

int number = 1, next = 1;
int turn[QTD_THREADS];

void* cs(void* p) {
	long idx = (long)p;
	printf("[%ld] iniciou\n", idx);
	while(1) {
		//<turn[i] = number; number++;>
		turn[idx] = __sync_fetch_and_add(&number,1);
		//<await(turn[i] == next);>
		while(!(turn[idx] == next)) usleep(50);
		//sc
		var_global++;
		printf("[%ld] vg: %d\n (ticket %d)\n", idx, var_global, turn[idx]);
		puts("..");
		//<next++>
		__sync_fetch_and_add(&next, 1);
	}
}

int main(void) {
	pthread_t threads[QTD_THREADS];

	for (int i = 0; i < QTD_THREADS; i++)
		turn[i] = 0;

	for (long i = 0; i < QTD_THREADS; i++) {
		pthread_create(&threads[i], NULL, cs, (void*)i);
	}

	sleep(20);

	return 0;
}

