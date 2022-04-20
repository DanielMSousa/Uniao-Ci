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
#include <signal.h>
#include <pthread.h>
#include <string.h>

int lebreChegouDestino = 0;
int pista;

struct arg_struct
{
  int indice;
  int maxSalto;
};

void* functionThread(void* parametros){
  struct arg_struct *args = parametros;

  int indice = (int)args->indice;

  int maxSalto = (int)args->maxSalto;

  int distanciaInicial = 0;


  while (lebreChegouDestino != 1 && distanciaInicial <= pista)
  {

    int salto = rand() % (maxSalto) + 10;;
    distanciaInicial += salto;
    printf("Lebre %d -- saltou %dcm (total %dcm)\n", indice, salto, distanciaInicial);
    sleep(1);

    if (distanciaInicial >= pista)
    {
      lebreChegouDestino = 1;
      printf("Lebre %d venceu!\n", indice);
      pthread_exit(NULL);
    }
  }

  pthread_exit(NULL);
    
}

void functionProcesso(int i, int salto_maximo) {
    int distancia_percorrida = 0;
    int salto;
    int tamPista = pista;

    while (lebreChegouDestino!=1&&distancia_percorrida <= tamPista)
    {
        salto = rand() % (salto_maximo) + 10;
        distancia_percorrida += salto;
        printf("Lebre %d -- saltou %dcm (total %dcm)\n", i, salto, distancia_percorrida);
        sleep(1);

        if (distancia_percorrida >= tamPista)
        {
            lebreChegouDestino = 1;
            printf("Lebre %d venceu!\n", i);
            kill(0, SIGKILL);
            exit(0);
            
        }

    }
    exit(0);
    
}


int main(int argc, char *argv[ ]) {
    int pid_original, pid_return, count = 0;
    // int number = atoi(argv[2]);
    int number;
    int indice = 0;
    int parallelismChoice = 0;
    int status, indiceLebre;
    printf("Digite a quantidade de Lebres que irão competir -> ");
    scanf("%d", &number);
    printf("Digite o tamanho da pista em cm -> ");
    scanf("%d", &pista);
    pthread_t Threads[number];
    int salto_maximo[number];
    
    // pista = atoi(argv[3]);
    for(int j = 0; j < number; j++){
            salto_maximo[j] = rand() % 30 + 1;
        }
    pid_original = getpid();
    printf("Nº Lebres: %d, Tamanho da Pista: %dcm\n", number, pista);

    if(strcmp(argv[1], "-t") == 0){
        for (long i = 0; i < number; i++) {
            struct arg_struct args;

            args.indice = i;
            args.maxSalto = salto_maximo[i];
            pthread_create(&Threads[i], NULL, functionThread, (void*)&args);
        }
        pthread_join(Threads[number - 1], NULL);
        return 0;
    }
    
    else if(strcmp(argv[1], "-p") == 0){


        for (int i = 0; i < number - 1; i++) {
		if (pid_original == getpid()) { 
            pid_return = fork();
            indice = i;
		} 
        
	} 
    
        if(pid_return != 0){
          functionProcesso(number - 1, salto_maximo[number-1]);
        }else{
            sleep(1);
            functionProcesso(indice, salto_maximo[indice]);
        }
    }
    

    return 0;

}
