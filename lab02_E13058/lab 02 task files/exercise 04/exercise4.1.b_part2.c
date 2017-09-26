/*
E/13/058
Exercise 4.1.b
 part b
capitalise letters and sends to the first process

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define STDIN 0
#define STDOUT 1


int main() 
{ 

	int fd1, fd2; 
	char* fifo = "/tmp/fifo"; 
	char* fifo2 = "/tmp/fifo2";

	char *tr_args[] = {"tr", "[:lower:]", "[:upper:]", NULL};

	mkfifo(fifo,0666);
	mkfifo(fifo2, 0666);

	fd1 = open(fifo, O_RDONLY);
	fd2 = open(fifo2, O_WRONLY);

	if (dup2(fd1, STDIN) == -1){
		printf("dup2()");
		return -1;}

	if (dup2(fd2, STDOUT) == -1){
		printf("dup2()");
		return -1;}

	if(execvp("tr", tr_args) == -1)
			exit(EXIT_FAILURE);

	close(fd1);
	close(fd2);

	exit(EXIT_SUCCESS);

    return 0; 
}

