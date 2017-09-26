#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>

void *function(void *arg)
{

printf("Thread says hi!\n");
sleep(2);

return NULL;
}

int main(void){
	pthread_t myThread;
	int i;

	for(i = 0;i<3;i++){

		pthread_create(&myThread,NULL,function,NULL);
		sleep(1);

	}
	
}