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

int main(int argc, char *argv[]) {
//pilha
	Pilha* p = criar_pilha();
	pilha_push(p, 2);
	printf("Olha inseri 2 na pilha\n");
	print_pilha(p);
	pilha_push(p, 4);
	pilha_push(p, 6);
	pilha_push(p, 9);
	printf("Agora inseri 4, 6 e 9 na pilha\n");
	print_pilha(p);
	printf("Removi o primeiro elemento!\n");
	pilha_pop(p);
	print_pilha(p);
	return 0;
}
