#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){

int pidO, pidC, retorno, a;
a = getpid();

printf("a == getpid() == %d\n", a);

retorno = fork();

if (retorno < 0) {
    printf("ERRO!\n");
}

if (retorno > 0) {
    a = getpid();
    pidO = getpid();
    printf("pidO = %d\n", pidO);
    printf("a apos fork = %d\n", a);
}

if (retorno == 0){

    pidC = getpid();
    printf("pidC =%d\n", pidC);
}

    return 0;
}