// 4) Faça um programa em C/C++ onde 6 threads (além da principal) gerarão uma letra aleatória 
// (caractere) cada. Estas letras deverão ser combinadas em uma palavra (uma string) na thread 
// principal (função  main), quedeverá exibi-la e também determinar se esta é um palíndromo ou não.
// Palíndromos são frases ou palavras quepodem ser lidas, indiferentemente, da esquerda para a direita, 
// conforme o sentido habitual da leitura, ou da direitapara a esquerda, sem que haja mudança da sua significação 
// (exemplos de palíndromos com 6 letras: “AAAAAA”,“ABAABA”, “ABCCBA”, “MUSSUM”). Repita este processo 10 vezes
// e use barreiras para sincronizar as threads. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#define QTD_THREADS 6

pthread_barrier_t allDone;
pthread_mutex_t create_string;
sem_t print_string;
char globalString[1000];

int isPalindrome(){
    char aux[1000];
    strcpy(aux, globalString);
    int i = 0;
    int j = 0;
    int size = 0;
    while (aux[size] != '\0')
{
    size++;
}
    i = size;
    i--;
    for(j = 0; j < size; j ++){
        if(aux[i] != globalString[j]){
            return 0;
        }
        i--;
    }
    return 1;
}

void* generate_and_concat(void* p){
    char char_ascii = (rand() % (122 - 97 + 1)) + 97;
    // long char_ascii = 122;
    pthread_mutex_lock(&create_string);
    //
    strcat(globalString, &char_ascii);
    //
    pthread_mutex_unlock(&create_string);
    //esperando pelas outras threads
    pthread_barrier_wait(&allDone);
    sem_post(&print_string);
}

//sem_wait(sem) --> while(1)

int main(void){
    pthread_t thread_char[QTD_THREADS];
    int k = 0;
    int retorno;
    sem_init(&print_string, 0, 0);
    pthread_barrier_init(&allDone, NULL, QTD_THREADS);
    pthread_mutex_init(&create_string, NULL);
    // sem_init(&create_string, 0, 0);
    while (k < 10)
    {
            
            globalString[0] = '\0';
            for (long i = 0; i < QTD_THREADS; i++)
        {
            pthread_create(&thread_char[i], NULL, generate_and_concat,(void*)i);
            
        }
        sem_wait(&print_string);//alguem setar print_string = 1
        retorno = isPalindrome();
        printf("Global String -- %s\n", globalString);
        if(retorno == 1){
            printf("É um palindromo\n");
        }else{
            printf("Não é um Palindromo\n");
        }
        sleep(1);
        k++;
  
            for (long i = 0; i < QTD_THREADS; i++)
        {
            pthread_join(thread_char[i], NULL);
        }  
    }

    sem_destroy(&print_string);
    pthread_mutex_destroy(&create_string);
    pthread_barrier_destroy(&allDone);
    
    return 0;
}