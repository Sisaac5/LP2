#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (phnum + (N-1)) % N
#define RIGHT (phnum + 1) % N

sem_t mutex;
sem_t garfo[N];

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

void test(int phnum) {
    if (state[phnum] == HUNGRY && 
        state[LEFT] != EATING && 
        state[RIGHT] != EATING) {
        state[phnum] = EATING;
        sleep(2);
        printf("Filósofo %d pega garfo %d e %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Filósofo %d está comendo\n", phnum + 1);
        sem_post(&garfo[phnum]);
    }
}

void take_fork(int phnum) {
    sem_wait(&mutex);
    state[phnum] = HUNGRY;
    printf("Filósofo %d está com fome\n", phnum + 1);
    test(phnum);
    sem_post(&mutex);
    sem_wait(&garfo[phnum]);
    sleep(1);
}

void put_fork(int phnum) {
    sem_wait(&mutex);
    state[phnum] = THINKING;
    printf("Filósofo %d coloca garfo %d e %d de volta na mesa\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Filósofo %d está pensando\n", phnum + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philospher(void* num) {
    while (1) {
        int* i = num;
        sleep(1); //thinking
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&garfo[i], 0, 0);

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
        printf("Filósofo %d está pensando\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}
