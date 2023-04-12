#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int num_processos = 5;

    printf("[pai] meu id é %d e o meu gpid é %d\n", getpid(), getpgid(0));

    num_processos = fork();
    if(num_processos != 0){
        printf("[pai] o pid do meu filho é %d\n", num_processos);
        printf("[pai] Morri\n");
        sleep(1);
        exit(0);
    }

    if(num_processos == 0){
        setpgid(0,getpid());
        printf("[clonado] meu id é %d e o meu gpid é %d\n", getpid(), getpgid(0));

        while (1)
        {
            printf("KKKK\n");
            sleep(1);
        }
        
    }

    sleep(2);
    killpg(num_processos,SIGKILL);

    return 0;
}
