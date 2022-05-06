#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMERO_PASSAGEIROS 10
#define CAPACIDADE_CARRO 5

int numero_passageiros_parque = 10;
int nAtualPassageirosCarro = 0;
int horarioFechamentoParque = 3;
//int turn[NUMERO_PASSAGEIROS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int carro_em_movimento = 0;
int em_espera_encher = 1;
int em_espera_esvaziar = 0;

void* thread_passageiros(void* p){
    long id = (long) p;
    while (horarioFechamentoParque != 0){
        /*entra no carro*/
        while(em_espera_esvaziar == 1);
        while(carro_em_movimento == 1);
        if(nAtualPassageirosCarro < CAPACIDADE_CARRO){
            printf("Entrei no carro...[%ld]\n", id);
            __sync_fetch_and_add(&nAtualPassageirosCarro,1);
            
            // printf("Esperando carro sair [%ld]\n", id);
            while(em_espera_encher == 1);
            // printf("Oba, o carro agora vai andar [%ld]\n", id);
            while(carro_em_movimento == 1);
            __sync_fetch_and_sub(&nAtualPassageirosCarro, 1);
            // printf("Sai do carro...[%ld]\n", id);
            // printf("Passeando pelo parque...[%ld]\n", id);
            sleep(5);//passeia pelo parque
        }
        

    }
    exit(0);
}

void* thread_carro(void*p){
    while (horarioFechamentoParque!=0)
    {
        em_espera_encher = 1;
        // printf("Sou o carro e estou esperando encher %d\n", em_espera_encher);
        
        while(nAtualPassageirosCarro < CAPACIDADE_CARRO);
        __sync_fetch_and_sub(&em_espera_encher, 1);
        __sync_fetch_and_add(&carro_em_movimento, 1);
        
        printf("Encheu agora vou da uma volta\n");
        sleep(3); //volta no carro
        __sync_fetch_and_sub(&carro_em_movimento, 1);
        __sync_fetch_and_add(&em_espera_esvaziar, 1);
        printf("terminei minha volta estou esperando os passageiros sairem do carro\n");
        while(nAtualPassageirosCarro != 0);
        __sync_fetch_and_sub(&em_espera_esvaziar, 1);
        __sync_fetch_and_sub(&horarioFechamentoParque, 1);
        

    }
    

}

int main(){
    pthread_t passageiros[NUMERO_PASSAGEIROS], carro; 
    pthread_create(&carro, NULL, thread_carro, NULL);
    for (int i = 0; i < NUMERO_PASSAGEIROS; ++i) {
		long arg = (long) i;
		if (pthread_create(&passageiros[i], NULL, thread_passageiros, (void *) arg) != 0) {
			// handle error
		}
	}

    while(horarioFechamentoParque != 0);
    printf("***********PARQUE FECHOU***********\n");
    for(int j = 0; j < NUMERO_PASSAGEIROS; j++){
        pthread_join(passageiros[j], NULL);
    }
    pthread_join(carro, NULL);
    return 0;
}