#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // usleep

#define NUMBER_THREADS 5

int global_var = 0;

int number = 1;
int next = 1;

int turn[NUMBER_THREADS] = { 0 };

void *cs (void *p)
{
	long idx = (long) p;

	printf("[%ld] Iniciou!\n", idx);

	while (1) {
		// < turn[i] = number; number = number + 1; >
		turn[idx] = __sync_fetch_and_add(&number, 1);

		// < await ( turn[i] == next ); >
		while (turn[idx] != next) {
			usleep(100);
		}
		
		// begin critical section

		global_var += 1;

		printf("[%ld] vg: %d\n(ticket: %d)", idx, global_var, turn[idx]);
		printf("..\n");
	
		// end critical section

		// < next = next + 1 >
		__sync_fetch_and_add(&next, 1);
	}

	return p;
}

int main (void)
{
	pthread_t threads[NUMBER_THREADS];

	for (int i = 0; i < NUMBER_THREADS; ++i) {
		long arg = (long) i;
		if (pthread_create(&threads[i], NULL, cs, (void *) arg) != 0) {
			// handle error
		}
	}

	sleep(2);

	return 0;
}
