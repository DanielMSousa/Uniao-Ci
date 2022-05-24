#include <stdio.h>
#include <stdlib.h>
#include "tad.h"


int main(int argc, char *argv[]) {

	Pilha* p = criar_pilha();
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
