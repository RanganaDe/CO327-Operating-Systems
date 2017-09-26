#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char **argv){
	
	execl("/bin/ls", "-l", argv[1], NULL);
	puts("Program ls has terminated");
	
	return 0;
}
