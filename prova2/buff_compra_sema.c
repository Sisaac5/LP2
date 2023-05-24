#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define VALUE_LIMIT 100
#define QTD_LOOP 5
#define BUFF_SIZE 10
#define QTD_PROD 1
#define QTD_CONS 5

int front = 0;
int rear = 0;
sem_t empty, full;

int buffer[BUFF_SIZE] = {0};

void* produtor(void* p) {
    int counter = 0;
    while (counter < BUFF_SIZE) {
        int value = 0;
        value = rand() % VALUE_LIMIT;
        sem_wait(&empty);
        buffer[rear] = value;
        sleep(1);
        printf("Produzi: %d\n", value);
        printf("Depositei em %d\n", rear);
        rear = (rear + 1) % BUFF_SIZE;
        sem_post(&full); 
        counter++;
    } 
    return 0;
}

void* consumidor(void* p) {
    int internal = 0;
    int counter = 0;
    while (counter < BUFF_SIZE) {
        sem_wait(&full);
        internal = buffer[front];
        printf("Capturei de buffer [%d]\n", front);
        front = (front + 1) % BUFF_SIZE;
        printf("Consumi: %d\n", internal);
        sem_post(&empty);
        counter++;
    }
    return 0;
}

int main(void) {
    pthread_t prod, cons;
    time_t t;

    srand(time(&t));

    sem_init(&empty, 0, BUFF_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prod, 0, produtor, 0);
    pthread_create(&cons,0, consumidor, 0);

    pthread_join(prod, 0);
    pthread_join(cons, 0);

    printf("[m] Buffer gerado\n");
    for (int i = 0; i < BUFF_SIZE; i++) {
        printf("[m] %d\n", buffer[i]);
    }

    return 0;

}
