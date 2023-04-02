#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

    int tam_pista, quant_lebres, pgid = 0;
    int pid_p = getpid();

    printf("Quantas lebres competem? ");
    scanf("%d", &quant_lebres);

    printf("Qual é o tamanho da pista? ");
    scanf("%d", &tam_pista);

    for(int i = 0; i < quant_lebres; i++){
        if(getpid() == pid_p){
            if(i == 0)
                pgid = fork();
            else
                fork();
        }

        if(getpid() != pid_p){
            setpgid(0, pgid);
            int dis_percorrida = 0, jump;
            while(dis_percorrida < tam_pista * 100){

                jump = rand() % 100;
                dis_percorrida += jump;
                printf("[lebre %d] pulei %d totalizando %d\n", i+1, jump, dis_percorrida);
                usleep(100);
            }

            printf("Lebre %d VENCEU\n", i+1);
            killpg(pgid,SIGKILL);
        }
    }

    wait(NULL);


    return 0;
}