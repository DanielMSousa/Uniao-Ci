#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

// com muitas threads causa problema de memoria


int lock = 0; // o boolean
int var_global = 0; // a var global

void* cs(void* p) { 
	long idx = (long)p; // index
	while(1) {
		while(__atomic_test_and_set(&lock, 1)); // testa e seta de forma atomica
		var_global++; // incrementa var global
		printf("secao critica indice %ld var: %d\n", idx, var_global);
		puts("..");
		lock = 0; // abre a porteira
		sleep(1);
		//printf("fora do crit %ld vg: %d\n", idx, var_global);
	}
}

int main(void) {
	pthread_t threads[3];

	pthread_create(&threads[0], NULL, cs, (void*)1);
	pthread_create(&threads[1], NULL, cs, (void*)2);
	//pthread_create(&threads[2], NULL, cs, (void*)3);
	sleep(5);
	return 0;
}
