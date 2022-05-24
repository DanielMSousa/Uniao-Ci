#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define QTD_THREADS 5

int var_global = 0;

int number = 1;
int next =1 ;
int turn[QTD_THREADS];

pthread_mutex_t number_inc_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t condicao_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condicao_cond = PTHREAD_COND_INITIALIZER;


void* func(void* p) {
long idx = (long)p;
while(1) {
    printf("fui criada\n");
pthread_mutex_lock(&number_inc_mutex);
printf("%ld passei do primeiro lock\n", idx);
number++;
turn[idx] = number;
pthread_mutex_unlock(&number_inc_mutex);
printf("%ld passei do primeiro unlock\n", idx);

pthread_mutex_lock(&condicao_mutex);
printf("%ld entrei no segundo lock condicao mutex\n", idx);
pthread_cond_wait(&condicao_cond, &condicao_mutex);
printf("%ld passe do segundo lock condicao mutex\n", idx);
 
var_global++;
printf("[CS.%ld] Alterou o valor para %d", idx, var_global);
puts("..");
//__sync_fetch_and_add(&next, 1);
pthread_cond_signal(&condicao_cond);
//pthread_mutex_unlock(&condicao_mutex);


}
return 0;
}



int main(void) {

pthread_t threads[QTD_THREADS];

for(int i = 0; i < QTD_THREADS; i++) {
    turn[i] = 0;}

for(long i = 0; i < QTD_THREADS; i++){
    pthread_create(&threads[i], NULL, func, (void*)i);
}
sleep(12);
return 0;
}