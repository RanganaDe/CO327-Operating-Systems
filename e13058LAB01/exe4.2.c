#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


int main() {
	int pid;

	char path[100];
	
	char arg[100];

	while(1) {

			printf("path:");
			scanf("%s",path);
			printf("argument:");
			scanf("%s",arg);

		pid = fork();
		
		if(pid<0) {
			perror("fork");
			exit(1);
		}

		if(pid == 0) {
			
			
			execl(path,"-l",arg,NULL);
		}
		else {
			wait(NULL);
		}
	}
}