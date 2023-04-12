#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_SLEEP_TIME 10

int* pid_array;

int main() {
	int qtd_proc;
	int pid_original;

	pid_original = getpid();

	printf("Digite um numero inteiro: ");
	scanf("%d", &qtd_proc);
	printf("Criando %d processos...\n", qtd_proc);
	pid_array = (int*)malloc(sizeof(int)*qtd_proc);
	fflush(stdout);
	for (int i = 0; i < qtd_proc; i++) {
		if (getpid() == pid_original) {
			int fork_return;
			fork_return = fork();
			if (getpid() != pid_original) {
				printf("[clone] ");
				printf("%d\n", getpid());
				int r_sleep;
				time_t t;
				srand(time(&t));
				r_sleep = rand() % getpid() % MAX_SLEEP_TIME;
				r_sleep++;
				printf("[clone] %ds\n", r_sleep);
				sleep(r_sleep);
				printf("[clone] fim\n");
				exit(r_sleep);
			} else {
				printf("[original] array setup\n");
				pid_array[i] = fork_return;
			}
		}	
	}

	if (getpid() == pid_original) {
		for (int i = 0; i < qtd_proc; i++) {
			printf("[o] %d\n", pid_array[i]);
		}		
		printf("[original] wait\n");
		int clone_exit;
		for (int i = 0; i < qtd_proc; i++) {
			waitpid(pid_array[i],					&clone_exit, 0);
			printf("[o] exit: %d\n", WEXITSTATUS(clone_exit));		
		}
		sleep(1);
		printf("[original] saindo...\n");
	}
	
	return 0;
}
