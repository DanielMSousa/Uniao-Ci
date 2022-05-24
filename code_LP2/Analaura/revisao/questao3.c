
// 3) Elabore (em código C/C++) uma solução para o problema da seção crítica. 
// Em um sistema bancário múltiplas threads podem realizar operações de débito e 
// crédito no saldo dos clientes – elabore uma solução para a manipulação do saldo utilizando locks,
//  implementando o protocolo de entrada utilizando uma instrução atômica (destaque 
//  qual é esta instrução e como ela funciona). 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define QTD_THREADS 5

int saldoCliente = 5000;
pthread_mutex_t changing;

void* debito(void* p){
    //funcao de debito
    long idx = (long)p;//pegar indice da thread
    int random_value = (rand() % 100) + 1;
    pthread_mutex_lock(&changing);//bloqueia para nenhuma outra thread entrar
    saldoCliente += random_value; // incrementa saldo do cliente
    printf("Thread Debit[%ld] -- Function Debit(%d) -- Client money now -- R$ %d\n", idx,random_value, saldoCliente);
    sleep(2);
    pthread_mutex_unlock(&changing);//libera para a proxima thread
 
}

void* credito(void* p){
    long idx = (long)p;
    int random_value = (rand() % 50) + 1;
    pthread_mutex_lock(&changing);
    saldoCliente -= random_value;
    printf("Thread Credit[%ld] -- Function Credit(%d) -- Client money now -- R$ %d\n", idx,random_value, saldoCliente);
    sleep(2);
    pthread_mutex_unlock(&changing);
}



int main(){
    
    pthread_t debito_t[QTD_THREADS], credito_t[QTD_THREADS];
    pthread_mutex_init(&changing, NULL);
    printf("Client Money before code execution -- R$ %d\n", saldoCliente);

    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&debito_t[i], NULL, debito,(void*)i);
        pthread_create(&credito_t[i], NULL, credito,(void*)i);
    }
    
    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_join(debito_t[i], NULL);
        pthread_join(credito_t[i], NULL);
        
    }
    pthread_mutex_destroy(&changing);
    printf("Client money -- R$ %d\n", saldoCliente);
    return 0;
} 