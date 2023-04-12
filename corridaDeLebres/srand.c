#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(){
    printf("Testando o srand\n");

    unsigned seed = (unsigned)time(NULL); 
    printf("Variable seed is %u\n", seed);

    srand(seed);

    printf("My seed is %u\n", (unsigned)time(NULL));
    printf("My seed after operation is %u\n", seed * getpid());

    printf("Numeros gerados pela seed\n");
    for(int i = 0; i < 10; i++){
        printf("%d\n", rand() % 100);
    }

    printf("Numeros gerados pela seed após a operacao\n");
    for(int i = 0; i < 10; i++){
        printf("%d\n", rand() % 100);
    }

    return 0;
}