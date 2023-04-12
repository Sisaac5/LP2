#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXEC_PATH "/home/aluno/Documentos/lpii/loop"

int main() {
	int fork_return;
	printf("Exemplo exec()\n");

	fork_return = fork();
	if (fork_return < 0) {
		printf("fork() error!\n");
		exit(0);
	} else {
		if (fork_return == 0) {
			//processo clonado
			char *args[] = { "./loop", "100000", NULL };
			printf("[c] irei executar o programa 'loop'\n");
			int exec_return = execv(EXEC_PATH, args);
			printf("[c] depois do exec(): %d\n", exec_return);
			//so sera exibido caso o exec de problema

		} else {
			//processo original
			int ret_val;
			waitpid(fork_return, &ret_val, 0);
			printf("[o] clonado finalizado!\n");
			//printf("[o] sou o original e vou acabar\n");
		}
	}

	return 0;
}
