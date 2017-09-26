#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/*
e/13/058
exercise 1.2
part b
*/

int main(int argc, char* argv[]){

	int source,target;
	size_t ret_in, ret_out;
	char Buffer[1000];

//error handling
	if(argc!=3){
		printf("wrong number of input arguements");
		return 1;
	}

//create source file descriptor
	source = open(argv[1],O_RDONLY);
	
	if(source == -1){
		printf("error opening source");
		return 1;
	}

//create target file descriptor
	target = open(argv[2],O_WRONLY|O_CREAT,S_IRUSR | S_IWUSR );
	if(target == -1){
		printf("error opening target");
		return 1;
	}


//copying from source to target

//read from source
	ret_in = read(source,Buffer,1000);
	if(ret_in == -1){
	printf("error reading from file");
	return 1;

	}

//write to target
	ret_out = write(target,Buffer,ret_in);
	if(ret_out == -1){
	printf("error writing to target file");
	return 1;
	}

	

//close file descriptors
	close(source);
	close(target);

return 0;

}





