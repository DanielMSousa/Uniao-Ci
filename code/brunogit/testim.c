#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	while(1);


}
