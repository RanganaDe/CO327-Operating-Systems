#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(void)
	{
		int pid,i;
		
		for(i=0;i<3;i++) {
			pid = fork();
			printf("fork - %d\n",pid);
		}
		
		if (pid < 0){
			perror("fork");
			exit(1);
		}
		
		if (pid == 0)
			printf("This is the child process \t pid = %d \t ppid = %d\n",getpid(),getppid());
			
		else{
			
			wait(NULL);
			printf("This is the parent process \t pid = %d \t ppid = %d\n",getpid(),getppid());
			
		}
		return 0;
			
	}
