#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>




int in1, in2; // o boolean
int var_global; // a var global
int last = 1; // vamos gerar uma certa ordem 

void* cs1(void* p) { 

	while(1) {
        last = 1; in1 = 1;
		while(in2 == 1 && last == 1);  // enquanto last tiver 1 e in2 nao for 0
		printf("cs1 secao critica last = %d in1 = %d in2 = %d\n", last, in1, in2);
		var_global++; 
        sleep(3);
        //printf("cs1 valor de var global: %d\n", var_global);
        //sleep(1);
		in1 = 0;
		//printf("cs1 fora do crit var: %d\n", var_global);
       // sleep(1);
	}
}
void* cs2(void* p) { 

	while(1) {
        last = 2; in2 = 1;
		while(in1 == 1 && last == 2); 
		printf("cs2 secao critica last = %d in1 = %d in2 = %d\n", last, in1, in2);
		var_global++; 
        sleep(3);
        //printf("cs2 valor de var global: %d\n", var_global);
       // sleep(1);
		in2 = 0;
		//printf("cs2 fora do crit var: %d\n", var_global);
       // sleep(1);
	}
}

int main(void) {
	pthread_t threads[2];

	pthread_create(&threads[0], NULL, cs1, NULL);
	pthread_create(&threads[1], NULL, cs2, NULL);
	
	sleep(35);
	return 0;
}
