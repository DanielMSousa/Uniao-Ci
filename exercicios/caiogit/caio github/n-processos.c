#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Essa é a forma de criar n processos com o fork, não é complicado de se entender.


*/ 



int main(void) {
	int n, fork_return, pid_original;

	printf("antes dos fork\n");

	pid_original = getpid(); //2275

	printf("digite n: ");
	scanf("%d", &n);
	n--;
//	fork_return = fork();

	for (int i = 0; i < n; i++) {
		if (pid_original == getpid()) { 
			//processo original
			fork();
		} else {
			//processo clonado
		} 
	} 
	printf("meu pid: %d, meu ppid: %d\n", 
		getpid(), getppid()); 

	printf("depois dos fork\n");
	//while(1); // para a main nao morrer e todas threads printarem, mas ai ela fica eternamente
	sleep(1);
	return 0;



}
