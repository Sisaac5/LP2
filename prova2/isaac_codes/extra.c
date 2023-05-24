#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 32
#define QTD_CONSUMIDOR 3

char buffer[BUFFER_SIZE] = {0};
sem_t full, empty;
int rear = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* produtor(){
    int counter = 0;

    while(counter < 128){
        char valor = (rand() % 25) + 'A';
        sem_wait(&empty);
        buffer[rear] = valor;
        printf("[produtor] produzi %c e armazenei em buffer %d\n", valor, rear);
        rear = (rear + 1) % BUFFER_SIZE;
        for(int i = 0; i < QTD_CONSUMIDOR; i++)
        	sem_post(&full);
        usleep(150);
        counter ++;
    }
    printf("[produtor] encerrando a produção\n");
}

void* consumidor(void *p){
    long index = (long) p;
    int front = 0, consumido = 0;;
    char leitura;
    while(1){
        sem_wait(&full);
        leitura = buffer[front];
        printf("[%ld]li do buffer[%d] o char %c\n", index, front, leitura);
        front = (front + 1) % BUFFER_SIZE;
        usleep((rand() % 70) + 30);

        pthread_mutex_lock(&mutex);
        __sync_fetch_and_add(&consumido, 1);
        if(consumido == 128){
            printf ("[consumidor %ld] finalizando o consumo\n", index);
            exit(0);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(){

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
	pthread_t t_prod, t_cons[QTD_CONSUMIDOR];

	pthread_create(&t_prod, NULL, produtor, NULL);
	for(long i = 0; i < QTD_CONSUMIDOR; i++){
		pthread_create(&t_cons[i], NULL, consumidor, (void*)i);
	}

	pthread_join(t_prod, NULL);
	for(int i = 0; i < QTD_CONSUMIDOR; i++){
		pthread_join(t_cons[i], NULL);
	}


    return 0;
}
