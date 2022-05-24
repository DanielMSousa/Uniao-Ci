#include <stdio.h>
#include <stdlib.h>

typedef struct pilha {
	int value;
	int dim;
	float *vet;
	
}Pilha;

Pilha* criar_pilha(void){
	Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
	pilha->dim = 2;
	pilha->vet = (float*) malloc(sizeof(float)*pilha->dim);
	pilha->value = 0;
	return pilha;
}

int pilha_vazia(Pilha* pilha){
	if(pilha->value == 0){
		return 1;
	}else {
		return 0;
	}
}

void pilha_push(Pilha* p, float v){
	if(p->dim == p->value){
		p->dim *= 2;
		p->vet =  (float*) realloc(p->vet, p->dim*sizeof(float));
	}
	p->vet[p->value++] = v;
}

float pilha_pop(Pilha* pilha){
	float v = pilha->vet[--pilha->value];
	return v;
}

void pilha_libera(Pilha* p){
	free(p->vet);
	free(p);
}
void print_pilha(Pilha* p){
    for (int i = p->value-1; i >=0 ; i--){
	    	printf(">%.0f\n", p->vet[i]);
	    }	
}
