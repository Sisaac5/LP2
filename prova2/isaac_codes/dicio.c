#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_barrier_t barreira;

void* escreve_arquivos(void *p){
    FILE *handle;
    char nome_aquivo[10];
    nome_aquivo[0] = (char) p;
    strcat(nome_aquivo, ".txt");

    handle = fopen(nome_aquivo, "wt");

    if(handle == NULL)
        printf("Erro\n");

    for(int j = 0; j < 26; j++){
        for(int k = 0; k < 26; k++){
            for(int l = 0; l < 26; l++){
                fprintf(handle, "%c%c%c%c\n", nome_aquivo[0], 'a' + j, 'a' + k, 'a' + l);
            }
        }
    }
    fclose(handle);
    printf("%c.txt feito!\n", nome_aquivo[0]);
    pthread_barrier_wait(&barreira);
}

int main(){
    pthread_barrier_init(&barreira, NULL, 27);

    pthread_t threads[26];
    for (int i = 0; i < 26; i++) {
        pthread_create(&threads[i], NULL, escreve_arquivos, (void*)('a' + i));
    }

    pthread_barrier_wait(&barreira);


    return 0;
}