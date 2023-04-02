#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int fim = 0;

typedef struct {
    int number;
    int dist;
} runner_t;

void* corrida(void* info){
    int distpercorrida = 0;
    runner_t *runner = (runner_t*) info;

    while(distpercorrida < runner->dist && !fim){
        int jump = rand() % 45;

        distpercorrida += jump;

        printf("[%d] pulou %d cm (total: %d)\n", runner->number, jump, distpercorrida);
    }

    if(distpercorrida > runner->dist){
        fim = 1;
        printf("A lebre %d VENCEU A CORRIDA!!\n", runner->number);
    }
}

int main(){
    int quant_lebres, tamanho_pista;

    printf("[main] Quantidade de lebres na corrida: ");
    scanf("%d", &quant_lebres);

    printf("[main] Tamanho da pista em metros: ");
    scanf("%d", &tamanho_pista);

    pthread_t lebresT[quant_lebres];
    runner_t lebres[quant_lebres];

    for(int i = 0; i < quant_lebres; i++){
        lebres[i].number = i + 1;
        lebres[i].dist = tamanho_pista;
    }

    for(int i = 0; i < quant_lebres; i++){
        pthread_create(&lebresT[i], NULL, corrida, (void*)&lebres[i]);
    }

    for(int i = 0; i < quant_lebres; i++){
        pthread_join(lebresT[i], NULL);
    }

    return 0;
}