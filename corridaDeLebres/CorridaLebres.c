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
    srand((unsigned)time(NULL) * runner->number);

    while(distpercorrida < runner->dist && !fim){
        int jump = rand() % 10;
        distpercorrida += jump;
        printf("[%d] pulou %d cm (total: %d)\n", runner->number, jump, distpercorrida);
        usleep(150);
    }

    printf("A lebre %d VENCEU A CORRIDA!!\n", runner->number);
    exit(0);

}

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Quantidade de argumentos inválida\n");
        return -1;
    }
    
    int quant_lebres, tamanho_pista;

    quant_lebres = atoi(argv[1]);
    tamanho_pista = atoi(argv[2]);

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