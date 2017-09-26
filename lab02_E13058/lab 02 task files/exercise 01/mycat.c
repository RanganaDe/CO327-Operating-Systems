
/*
Exercise 1.2 part a
 
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc , char *argv[] )
{
	int out;
	size_t size = 1000;

	//reads a text file
	

	out = open(argv[1], O_RDONLY);
	
	if(out == -1)
	{
		fprintf(stderr,"Couldn't open the file\n");
		return 1;
	} 

	

	char* buffer = malloc(size+1); /* size of a char is 1. This buffer holds the read back value. */

	size_t ret = read(out,buffer,size);

	if(ret == -1)
	{
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}
	
	//writes to the standard output	
	
	buffer[ret] = '\0'; /* we have to null terminate the string ourselves. */
	
	
	printf("The string read back is: %s\n",buffer);
	/* In case there was something already written in the file, the text read back might not be the same as what was written */
	
	
	free(buffer);

	ret = close(out);

	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}

	return 0;
}
