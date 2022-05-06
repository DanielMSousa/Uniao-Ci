#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int in1, in2;
int var_global;  

void* cs1(void* p){
    while (1)
    {
        while (in2 == 1); /// so progride se in1 != 1;
        in2 = 1;
        printf("Entrei na cs1\n");
        sleep(3);
        var_global++;
        printf("cs1 --> var_global: %d\n", var_global);
        in1 = 0;
        printf("saindo do cs1\n");
        sleep(1);
    }
    
}

void* cs2(void* p){
    while (1)
    {
        while (in1 == 1);
        in1 = 1;
        printf("Entrando cs2\n");
        sleep(3);
        var_global++;
        printf("cs2 --> var_global: %d\n", var_global);
        in2 = 0;
        printf("saindo do cs2\n");
    
    }
}

int main(void){
    pthread_t t1, t2;
    var_global = 0;
    in1 = 0;
    in2 = 0;
    pthread_create(&t1, NULL, cs1, NULL);
    pthread_create(&t2, NULL, cs2, NULL);

    sleep(20);
  
    return 0;
}