/*
exercise 2.1
part d
E/13/058
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define READ_END 0
#define WRITE_END 1


/*
parent reads a string from user
send it to the child
child capitalize each letter
sends back the string to parent
parent displays it



*/


int main(int argc, char* argv[]){

	int pipe_1[2],pipe_2[2];
	
	pid_t pid;
	


	//create pipes
		if(pipe(pipe_1)) 
	{
		perror("Pipe 1 creation");
		return -1;
	}

		if(pipe(pipe_2)) 
	{
		perror("Pipe 2 creation");
		return -1;
	}
 	//create child processes with fork ()
	pid = fork();

	if(pid < 0) 
	{
		perror("Fork");
		return -1;
	}

 //parent 
	if(pid>0){
		char buff2[1000];
		close(pipe_1[READ_END]);
		//write to write end of pipe_1
		write(pipe_1[WRITE_END],argv[1],(int)strlen(argv[1]));


		close(pipe_1[WRITE_END]);
		close(pipe_2[WRITE_END]);
		sleep(5);
		//Read from read end of pipe_2 (user string capitalised and sent from pipe_1)
		int count = read(pipe_2[READ_END],buff2,1000);
		
		buff2[count] = '\0';

		close(pipe_2[READ_END]);

		//Write it to the standard output through write end of pipe_2
		write(STDOUT_FILENO, &buff2, (int)strlen(buff2));

		exit(EXIT_SUCCESS);




	}

	//child
if(pid == 0){


	char buff[1000];
	//char cap[1000];
	
	int count;
	int i = 0;


	close(pipe_1[WRITE_END]);
	sleep(5);
	
	count = read(pipe_1[READ_END],buff,1000);
	buff[count] = '\0';

    //capitalise
   while(buff[i] != '\0')
   {
      buff[i]= toupper(buff[i]);
      i++;
   }

	// send back the capitalised value through the pipe_2
	close(pipe_2[READ_END]);
	write(pipe_2[WRITE_END],buff,(int)strlen(buff));
	close(pipe_2[WRITE_END]);

exit(EXIT_SUCCESS);
	


}













return 0;
	}