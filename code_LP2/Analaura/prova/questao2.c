// (Questão 2 - 5 pontos) Faça um programa em C/C++ que siga as especificações 
// abaixo:
// - declare uma variável global do tipo double; 
// - faça o programa criar um processo que gere um valor aleatório (entre 0 e 99)
// e faça este processo retornar o valor para o processo original, que estará 
// bloqueado, aguardando.
// - o programa deverá então criar 10 threads, que executarão uma função que 
// recebe como parâmetro  valor inteiro que representa um índice único (de 0 a 9).
// - a função deverá verificar se seu identificador é par: caso positivo, a função
// deve realizar um laço de repetição que faça 50 incrementos (+1) na variável 
// global; caso o identificador não seja par, a função deve realizar um laço que
// faça 30 decrementos (-1) na variável global. A cada iteração essa função deve
// exibir o identificador da thread e o novo valor da variável global
// - depois dos laços, as threads cujo identificador for par devem dormir um tempo
// aleatório entre 1s e 4s; as threads cujo identificador for impar dormem um 
// tempo fixo de 2s.
// - após o término de todas as threads, a thread principal deverá exibir o valor 
// final da variável global. 
 
// Comente o código explicando o conceito de concorrência (e suas diferentes 
// formas de realização nos SO mais facilmente encontrados). Explique quais 
// são os elementos do Sistema Operacional e da arquitetura do computador 
// envolvidos na execução do programa e como se comportam para que a lógica 
// implementada seja executada de forma concorrente. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

#define QTD_ARQUIVOS 6

double varible;

//funcao que acrescenta e diminui thread
void* thread_function(void* value) {
    //int number = (int) varible;
    int k = (long) value;
    int sleep_par = rand()%4;
    int sleep_impar = 2;
    if(k % 2 == 0){
        //se numero par incrementa 50 vezes
        for(int i = 0; i<50; i++){
            varible++;
            printf("Thread %d - variavel global:  %0.f\n",k, varible);
        }
        
    }else{
        //se numero impar decrementa 30 vezes
        for(int j = 0; j<30; j++){
            varible--;
            printf("Thread %d - variavel global:  %0.f\n",k, varible);
            
        }
        
    }
    if(k % 2 == 0){
         if(sleep_par == 0){
             sleep_impar = 1;
         }
         sleep(sleep_par);
        
    }else{
        sleep(sleep_impar);
    }
    // printf("Thread: %d\nVar global: %0.f\n", k, varible);
}

int main(void) {
	int pid_original;
	pthread_t threads[10];
	int ret_th[10];
    int return_value, ret_val_clone, random_value, exit_value_clone;
    //salva pid da main
    pid_original = getpid();

    return_value = fork();
    
     if(return_value > 0) {
        //espera clone terminar de calcular o random
        waitpid(return_value, &exit_value_clone,0);
        varible = WEXITSTATUS(exit_value_clone);
        printf("o numero random foi %0.f\n", varible);

    } else {
        // clone calcula o random
        srand(getpid());
        ret_val_clone = rand() % 100;
        exit(ret_val_clone);
    }
       //executa somente na main
    if(pid_original==getpid()){
        waitpid(return_value, &exit_value_clone, 0);
        //cria threads
        printf("Criando threads agora!\n");
        for (long i = 0; i < 10; i++) {
		pthread_create(&threads[i], NULL, thread_function,(void*)i);
	    }

        sleep(5);
        //threads voltam para a main
        for (int i = 0; i < 10; i++) {
            pthread_join(threads[i], (void*)&ret_th[i]);
        }
        //mostra valor final da variavel global
        printf("MAIN -> Variavel global: %0.f\n", varible);
    }
	

	

	return 0;

}
//A memoria e o processador são utilizados na questão.