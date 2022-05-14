#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define QTD_PASSEGERS 10
#define CAPACITY_CAR 4
#define MAX_RIDES 2

pthread_mutex_t enter;
pthread_mutex_t leave;

sem_t are_boarding;
sem_t all_boarded;
sem_t are_unboarding;
sem_t all_unboarded;

int on_board_passeger = 0;
int number_rides = 0;
int unboarded_passegers = 0;
int current_ride = 0;

void load(){
    printf("Ride #%d will begin, time to load!\n", current_ride+1);
	printf("This car's capacity is %d\n", CAPACITY_CAR);
	sleep(2);
}
void run(){
	printf("The car is full, time to ride!\n");
	sleep(2);
	printf("The car is now riding the roller coaster!\n");
	sleep(5);
}
void unload(){
	printf("The ride is over, time to unload!\n");
	sleep(2);
}
void board(long id){
	printf("Passenger [%ld] entering in the car...\n", id);
	sleep(rand()%2);
}
void unboard(long id){

	printf("Passenger [%ld] leving the car...\n", id);
	sleep(rand()%2);
}

void* passegers(void* p){
    long idx = (long) p;
    while (1)
    {
        
        sem_wait(&are_boarding);
        //thread entra no carro e bloqueia 

        //bloco de codigo executado uma thread por vez
        pthread_mutex_lock(&enter);
        on_board_passeger++; // Entra uma thread de cada vez no carro
        board(idx); // tempo para embarcar
        if(on_board_passeger == CAPACITY_CAR){
            sem_post(&all_boarded); // Se tem passageiros suficientes, 
            //avisa que pode começar a corrida usando sem_post(&all_boarded) --> (all_boarded++)
            //on_board_passeger = 0; 
        }
        pthread_mutex_unlock(&enter);
        //bloco de codigo executado uma thread por vez

        sem_wait(&are_unboarding);

        //bloco de codigo executado uma thread por vez
        pthread_mutex_lock(&leave);
        on_board_passeger--;
        unboard(idx);
        if(on_board_passeger == 0){
            sem_post(&all_unboarded);
        }
        pthread_mutex_unlock(&leave);
        //bloco de codigo executado uma thread por vez
    }
    return NULL;
}

void* car(void* p){
    int i;
    while (current_ride < MAX_RIDES)
    {
        load();
        for (int i = 0; i < CAPACITY_CAR; i++) sem_post(&are_boarding); //carro libera entrada 
        sem_wait(&all_boarded); // apos todos dentro do carro, o carro 
        run();
        unload();
        for (int i = 0; i < CAPACITY_CAR; i++) sem_post(&are_unboarding);
        sem_wait(&all_unboarded);
        printf("The car is empty\n\n");
        current_ride++;
    }
    return NULL;
    
}

int main(void){
    pthread_t car_thread, passegers_thread[QTD_PASSEGERS];
    long i;
    pthread_mutex_init(&enter, NULL);
    pthread_mutex_init(&leave, NULL);
    sem_init(&are_boarding, 0, 0);
    sem_init(&all_boarded, 0, 0);
    sem_init(&are_unboarding, 0, 0);
    sem_init(&all_unboarded, 0, 0);

    printf("Today the roller coaster will ride %d times!\n", MAX_RIDES);
	printf("There are %d passengers waiting in the roller coaster queue!\n\n", QTD_PASSEGERS);

    pthread_create(&car_thread, NULL, car, NULL);
    for (i = 0; i < QTD_PASSEGERS; i++)
    {
        pthread_create(&passegers_thread[i], NULL, passegers, (void*)i);
    }
    pthread_join(car_thread, NULL);
    printf("That's all rides for today, the roller coaster is shutting down.\n");
    pthread_mutex_destroy(&enter);
    pthread_mutex_destroy(&leave);
    sem_destroy(&are_boarding);
    sem_destroy(&all_boarded);
    sem_destroy(&are_unboarding);
    sem_destroy(&all_unboarded);
    
    return 0;
}