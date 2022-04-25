#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int functionSoma(int n, int n2){
    printf("Soma -> n : %d, n2: %d\n", n, n2);
    sleep(3);
    return n + n2;
}

int functionMultiplica(int n, int n2){
    printf("Multi -> n : %d, n2: %d\n", n, n2);
    sleep(4);
    return n*n2;
}


int main(){

    int n, n2, retorno, pid_inicial, soma, multipli, endereco;
    n = 5;
    n2 = 10;
    pid_inicial = getpid();
    retorno = fork();

    if(retorno != 0){
        //original
     
        multipli = functionMultiplica(n, n2);
        waitpid(retorno, &endereco, 0);
    }else{
        //clone
        soma = functionSoma(n, n2);
        exit(soma);
    }
    
    if(pid_inicial == getpid()){
        //wait
        printf("A multiplicação da %d, a soma da %d\n", multipli, WEXITSTATUS(endereco));
    }
    
    
    return 0;
}