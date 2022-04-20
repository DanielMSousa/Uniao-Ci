// Faça um programa em C/C++ que simula uma corrida de lebres, usando threads e 
// processos. O programa deverá receber 3 parâmetros na sua execução: 
// - se usará processos ou threads; 
// - quantas instâncias (lebres) serão criadas para a corrida;
// - e um valor inteiro, que representa o tamanho da pista da corrida em metros.

// Exemplo de execução:

// 	$ ./corrida -t 5 1000 (5 lebres/threads, pista de 1000m)
// 	lebre 0 saltou 30cm (total: 30)
// 	lebre 2 saltou 42cm (total: 42)
// 	...
// 	lebre 2 saltou 31cm (total: 1002)
// 	lebre 2 venceu! 

// 	$ ./corrida -p 10 500 (10 lebres/processos, pista de 500m)
// 	lebre 1 saltou 20cm (total: 20)
// 	lebre 0 saltou 43cm (total: 43)
// 	...
// 	lebre 3 saltou 44cm (total: 520)
// 	lebre 3 venceu!

// Os processos / threads executarão a função que representa as lebres nessa 
// corrida fictícia; a função que receberá dois parâmetros: um valor inteiro que
// identifique a lebre (seu índice) e um valor inteiro que represente a distância
// máxima do salto dessa lebre em cm. A função então simulará a corrida de uma 
// lebre através de um loop onde cada iteração é um 'salto', que acontece a partir
// da geração de um valor aleatório entre 10 e o valor do salto máximo definido
// para aquela instância de "lebre" (considerando valores expressos em cm).

// Faça as lebres "correrem" nessa "pista" com o tamanho definido na execução do
// programa. Para cada vez que a função de cada processo/thread (lebre) executar
// a geração de valores aleatórios uma soma de todos os saltos deverá ser 
// armazenada em uma variável com o quanto a lebre já percorreu da pista (uma 
// variável int no escopo da função da lebre). A função permanece no loop, 
// "saltando", até que o valor acumulado seja igual ou superior ao tamanho da 
// pista.

// A cada "salto" (iteração realizada pela função associada ao processo ou a 
// thread), deverá ser exibida uma mensagem contendo a distância do salto 
// efetuado e qual distância total percorrida (dormindo 1s - função sleep - até 
// que dê outro salto). A primeira 'lebre' (thread ou processo) que finalizar sua
// função (ou seja, tenha a variável que represente o quanto a lebre já percorreu
// com valor maior ou igual ao tamanho da pista) deverá exibir uma mensagem onde 
// se declara vencedora e o programa deverá ser finalizado. 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>



void* functionThread(void* i){
    long p = (long)i;
    printf("Hello %ld\n", p);
    
}
void functionProcesso(int i, int salto_maximo, int pista) {
    int distancia_percorrida = 0;
    int salto;
   

    while (distancia_percorrida < pista)
    {
        salto = rand() % (salto_maximo) + 10;
        distancia_percorrida += salto;
        printf("Lebre %d -- saltou %dcm \n", i, salto);
        sleep(1);
    }
    //exit(1);
}


int main(int argc, char *argv[ ]) {
    int pid_original, pid_return, count = 0;
    int number = atoi(argv[2]);
    int pista = atoi(argv[3]);
    int parallelismChoice = 0;
    pthread_t Threads[number];
    int indice = 0;
    int salto_maximo[number];
    int status;
    /*
    1 -> processo
    2 -> thread
    */
    if(strcmp(argv[1], "-p") == 0){
        parallelismChoice = 1;
        printf("Escolheu processo\n");

    }else if(strcmp(argv[1], "-t") == 0){
        parallelismChoice = 2;
        printf("Escolheu thread\n");
    }
    pid_original = getpid();
    printf("numero: %d, pista: %d\n", number, pista);

    if(parallelismChoice == 2){
        for (long i = 0; i < number; i++) {
        pthread_create(&Threads[i], NULL, functionThread, (void*)i);
        }
    }

    
    
    else if(parallelismChoice == 1){
        //processo
        for(int j = 0; j < number; j++){
            salto_maximo[j] = rand() % 30 + 1;
        }

        for (int i = 0; i < number - 1; i++) {
		if (pid_original == getpid()) { 
			//processo original
            //printf("i antes do fork %d\n", i);
            //printf("meu pid: %d, meu ppid: %d\n", getpid(), getppid()); 
            pid_return = fork();
            indice = i;
            
			
		} else {
           // printf("Clone:: meu pid: %d, meu ppid: %d\n", getpid(), getppid()); 
            
		} 
        
	} 
    
    
        if(pid_return != 0){
            functionProcesso(number - 1, salto_maximo[number-1], pista);
        }else{
            functionProcesso(indice, salto_maximo[indice], pista);
        }
        
	    // printf("meu pid: %d, meu ppid: %d\n", 
		// getpid(), getppid()); 

	    
    }

    if(getpid() == pid_original){
        wait(&status);
        printf("Staus %d\n", WEXITSTATUS(status));
        return 0;
    }

    return 0;

}
