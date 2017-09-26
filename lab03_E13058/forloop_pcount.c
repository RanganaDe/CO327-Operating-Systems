#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){

	int i;

	for(i = 0;i<3;i++){
		fork();
		printf("pid = %d,ppid = %d,i = %d\n",getpid(),getppid(),i);
		
	wait(NULL);



	}
	



}