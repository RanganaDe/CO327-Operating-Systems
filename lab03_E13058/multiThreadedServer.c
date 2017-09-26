#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/*
E/13/058
De Silva M.D.R.A.M
Lab 03 part 04 : Multi threaded server.

Instructions

Compile with -pthread and run the server
test the client with the use of another teminal (nc 127.0.0.1 32000) and see the output in the server terminal.

*/


typedef struct clientDetails{
	int client_fd; 
	unsigned int client_length;
	struct sockaddr_in client_address;

}client_details;


void* handle_client(void*);

int main()
{
	int listenfd;
	int* connfd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;

	listenfd=socket(AF_INET,SOCK_STREAM,0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);

	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,5);

	clilen = sizeof(cliaddr);
	while (1)
	{
		connfd = malloc(sizeof(int));
		*connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);


		/* now create a new thread, pass it the socket and run the thread. */

		client_details *clientDetails = malloc(sizeof(client_details));
		clientDetails -> client_fd = *connfd;
		clientDetails -> client_length = clilen;
		clientDetails -> client_address = cliaddr;

		pthread_t mythread;

		//create thread
		if ( pthread_create(&mythread, NULL, handle_client, clientDetails)){
			printf("error creating thread.");
			abort();
		}

		
		
	}
	exit(0);
}

void* handle_client(void* connfd)
{
	/* read a string sent by the client, 
	 * print it and then send the string 
	 * "Hello from the server" to the client*/
	
	
	client_details* client_connection = (client_details*)connfd;

	int client_fd = client_connection -> client_fd;

	unsigned int client_length = client_connection-> client_length;

	struct sockaddr_in client_address = client_connection -> client_address;

	char buff[1000];

	int n;

	// recieve client message
	n = recvfrom(client_fd, buff, 1000, 0, (struct sockaddr*)&client_address, &client_length);


	buff[n-1] = '\0';
	printf("%s\n", buff);
	char * welcome = "Hello client! This is the Server responding! \n";
	

	// send message to client
	if(sendto(client_fd, welcome, strlen(welcome), 0, (struct sockaddr*) &client_address, client_length)<0){

		printf("error sending message to client\n");
	}

	// Close port
	close(client_fd);

	// free allocated memory
	free(connfd);

	return NULL;
}
