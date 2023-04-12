#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define EXEC_PATH1 "/home/aluno/aluno/LP2-master/corridaDeLebres/processos"
#define EXEC_PATH2 "/home/aluno/aluno/LP2-master/corridaDeLebres/threads"

int main(int argc, char *argv[]){

    if(argc != 4)
        return -1;

    if(!strcmp(argv[1], "-t")){
        char *args[] = { "./threads", argv[2], argv[3], NULL};
		printf("Entrando no modo threads\n");
		int exec_return = execv(EXEC_PATH2, args);
        printf("[Erro: %d\n", exec_return);
    }

    else if(!strcmp(argv[1], "-p")){
        char *args[] = { "./processos",argv[2], argv[3], NULL};   
		printf("Entrando no modo processos\n");
		int exec_return = execv(EXEC_PATH1, args);
        printf("Erro %d\n", exec_return);
    }

    else{
        printf("Argumentos inváldos\nDigite <-p> para processos ou <-t> para threads\n");
    }

    return 0;
}