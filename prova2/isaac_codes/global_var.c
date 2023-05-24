#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int x = 0, y = 0;
sem_t semaforo_x, semaforo_y;

void* soma_var(void* p){
    int index = (int) p;
    srand(index);

    if(index % 2 == 0){
        while(x+y < 2000){
            sem_wait(&semaforo_x);
            x += (rand() % 95) + 5;
            usleep(200);
            sem_post(&semaforo_x);

            printf("A thread %d incrementou x\n", index);

            sem_wait(&semaforo_y);
            y += (rand() % 49) + 1;
            usleep(100);
            sem_post(&semaforo_y);

            printf("A thread %d incrementou y\n", index);
        }   
    }
    else{
        while(x+y < 2000){
            sem_wait(&semaforo_x);
            x += (rand() % 29) + 1;
            usleep(100);
            sem_post(&semaforo_x);

            printf("A thread %d incrementou x\n", index);

            sem_wait(&semaforo_y);
            y += (rand() % 80) + 15;
            usleep(250);
            sem_post(&semaforo_y);

            printf("A thread %d incrementou y\n", index);
        }
    }
    printf("[%d] x = %d, y = %d\n",index, x, y);
    return NULL;
}

int main(){

    pthread_t threads[10];
    sem_init(&semaforo_x,0,1);
    sem_init(&semaforo_y,0,1);

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, 
                        soma_var, (void*)i);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("[main] x = %d, y = %d\n", x, y);

    return 0;
}