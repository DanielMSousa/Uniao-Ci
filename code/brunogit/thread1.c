#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* funcao1(void* p) {
	printf("Funcao 1: iniciando\n");
	sleep(1);
	printf("Funcao 1: 1\n");
	sleep(1);
	printf("Funcao 1: 2\n");
	sleep(1);
	printf("Funcao 1: 3\n");
	sleep(1);
	printf("Funcao 1: 4\n");
	sleep(1);
	printf("Funcao 1: 5\n");
	sleep(1);
	printf("Funcao 1: 6\n");
printf("falta exibir o fim da funcao 1 !\n");
sleep(15);
	printf("Funcao 1: saindo...\n");


}

void funcao2() { 
	printf("Funcao 2: iniciando\n");
	sleep(1);
	printf("Funcao 2: 1\n");
	sleep(1);
	printf("Funcao 2: 2\n");
	sleep(1);
	printf("Funcao 2: 3\n");
	printf("Funcao 2: saindo...\n");
}

void funcao3() { 
	printf("Funcao 3: iniciando\n");
	sleep(1);
	printf("Funcao 3: 1\n");
	sleep(1);
	printf("Funcao 3: 2\n");
	sleep(1);
	printf("Funcao 3: 3\n");
	printf("Funcao 3: saindo...\n");

}

int main(void) {
	pthread_t t1;

	printf("Funcao main: inicio\n"); 

	pthread_create(&t1, NULL, funcao1, NULL);
	funcao2();

    //printf("o join começa aqui\n");
	//pthread_join(t1, NULL);
    printf("nao fiz o join\n"); // para fazer o join comenta essa parte
	funcao3();

	printf("Funcao main termina em 5 segundos...\n");
	sleep(5);
    printf("fim da main !!!\n");

	return 0;
}
