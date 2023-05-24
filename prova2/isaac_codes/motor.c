#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

float temp = 600;
sem_t sema;

void* aumenta_temp(){
    while(1){
        sem_wait(&sema);
        temp += rand()%100 - 10;
        printf("temp = %.2f\n", temp);
        sem_post(&sema);
        usleep(200);
    }
}

void* diminui_temp(){
    int counter = 0;
    while(counter < 5){
        sem_wait(&sema);
        if(temp >= 1000){
            counter ++;
            printf("resfriando o motor...\n");
            usleep(300);
            temp = 600;
            if(counter == 3)
                return NULL;
        }
        sem_post(&sema);
    }
    return NULL;
}

int main(){
    time_t t;
    pthread_t threads[2];

    srand((unsigned) time(&t));
    sem_init(&sema,0,1);

    pthread_create(&threads[0], NULL, aumenta_temp, NULL);
    pthread_create(&threads[1], NULL, diminui_temp, NULL);

    pthread_join(threads[1], NULL);

    printf("finalizando programa...\n");
    exit(0);
    return 0;
}