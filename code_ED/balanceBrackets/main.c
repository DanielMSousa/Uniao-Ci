#include <stdio.h>
#include <stdlib.h>

/*
2
3
*/

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
void pilha_push(Pilha* p, char v){
	if(p->dim == p->value){
		p->dim *= 2;
		p->vet =  (float*) realloc(p->vet, p->dim*sizeof(float));
	}
	p->vet[p->value++] = v;
}
char pilha_pop(Pilha* pilha){
   
    
	char v = pilha->vet[--pilha->value];
	return v;
}
void pilha_libera(Pilha* p){
	free(p->vet);
	free(p);
}
void print_pilha(Pilha* p){
    for (int i = p->value-1; i >=0 ; i--){
	    	printf(">%c\n", (char) p->vet[i]);
	    }	
        printf("fim do print\n");
}

int main(int argc, char *argv[]) {
//pilha
	Pilha* p = criar_pilha();
    char bracket[] = {'[', '(', ')', '{', '}', ']'};
    int result = 1;
    char aux;
    for(int i = 0; i < 6; i++){
        if(bracket[i] == '[' || bracket[i] == '(' || bracket[i] == '{'){
            pilha_push(p, bracket[i]);
        }else{
            if(p->value == 0){
                result = 0;
                break;
            }else{
                aux = pilha_pop(p);
                printf("%c == %c?\n", aux, bracket[i]);
                if(aux == '(' && bracket[i] != ')' || aux == '[' && bracket[i] != ']' || aux == '{' && bracket[i] != '}' ){
                    result = 0;
                    break;
                }
            }
        }
    }
    if(p->value == 0 && result == 1){
        result = 1;
    }else{
        result = 0;
    }
    if(result == 1){
        printf("Brackets balanced!\n");
    }else{
        printf("Brackets not balanced!\n");
    }
	return 0;
}
