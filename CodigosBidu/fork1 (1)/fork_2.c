#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

	int fork_return;

	fork_return = fork();

	if (fork_return == -1) {
		printf("fork() error!\n");
		exit(-1);
	} else if (fork_return == 0) {
		int var;
		printf("[processo clonado] ");
		printf("meu pid: %d\n", getpid());
		printf("[processo clonado] ");
		printf("pid ascendente: %d\n", getppid());
		printf("[pc] Digite um inteiro: ");
		scanf("%d", &var);
		printf("[pc] Valor inserido: %d\n", var);
		exit(var);
	} else {
		int wait_return;
		printf("[processo original] ");
		printf("meu pid: %d\n", getpid());
		printf("[processo original] ");
		printf("pid descendente: %d\n", fork_return);
		printf("[po] aguardando clonado\n");
		wait(&wait_return);
		printf("[po] clonado saiu: %d\n", WEXITSTATUS(wait_return)); 
		printf("[po] clonado finalizado\n");		
	}

	return 0;
}

