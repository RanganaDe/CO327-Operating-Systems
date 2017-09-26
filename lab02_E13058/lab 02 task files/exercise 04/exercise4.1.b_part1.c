/*
E/13/058
exercise 4.1.b 
part 1

*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>



int main(int argc, char **argv)
{ 	

	int fd1, fd2; 
	char buf[1000]; 
	char* fifo = "/tmp/fifo"; 
	char* fifo2 = "/tmp/fifo2";

	mkfifo(fifo, 0666);
	mkfifo(fifo2, 0666);

	//write to pipe
	fd1 = open(fifo, O_WRONLY);
	write(fd1, userString, strlen(argv[1])); 
  	  close(fd1); 

    // Read data from pipe
	fd2 = open(fifo2, O_RDONLY);
   	 read(fd2, buf, 1000); 

   	 close(fd2); 
	unlink(fifo);
	unlink(fifo2);

    return 0; 
}

