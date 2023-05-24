#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define VALUE_LIMIT 100
#define QTD_LOOP 5

int buf;
sem_t empty, full;

void* produtor(void* p) {
    int counter = 0;
    while (counter < QTD_LOOP) {
        int value = rand() % VALUE_LIMIT;
        sem_wait(&empty);
        buf = value;
        printf("Produzi: %d\n", value);
        sleep(1);
        sem_post(&full);
        counter++;
    }
    return 0;
}

void* consumidor(void* p) {
    int counter = 0;
    int internal = 0;
    while (counter < QTD_LOOP) {
        sem_wait(&full);
        internal = buf;
        printf("Consumi: %d\n", internal);
        sem_post(&empty);
        counter++;
    }
    return 0;
}

int main(void) {
    pthread_t t_prod, t_cons;
    time_t t;
    
    srand(time(&t));

    sem_init(&empty, 0 , 1);
    sem_init(&full, 0, 0);

    pthread_create(&t_prod, 0, produtor, 0);
    pthread_create(&t_cons, 0, consumidor, 0);

    pthread_join(t_prod, 0);
    pthread_join(t_cons, 0);

    return 0;
}