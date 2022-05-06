#include <stdio.h>
#include <stdlib.h>
#include "tad.h"


int main(int argc, char *argv[]) {
//pilha
	Pilha* p = criar_pilha();
	//transformar decimal em binario
    //10
    int value = 6;
    int resto = value;
    int binarioNum;
    while (value > 0)
    {
        binarioNum = value % 2;
        value = value / 2;
        pilha_push(p, binarioNum);
    }
    print_pilha(p);
    
	return 0;
}
