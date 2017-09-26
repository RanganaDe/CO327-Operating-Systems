/*
E/13/058 
Co327 lab 04 part four
The reader-writer problem
The same data resource is read by certain threads (called readers) and written by other threads (called
writers) concurrently. To avoid readers reading wrong data and writers corrupting the data resource,
only one writer can write at the same time and no readers could read data when a writer is writing. But
when there are only readers reading data, any number of readers could read the data concurrently. 
*/

#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <semaphore.h> 


#define CAPACITY 20


sem_t writeLock;
sem_t readLock;
int readers = 0;
int  data[CAPACITY];


void* reader(void * x){

	while (1){
		sem_wait(&readLock);
		readers++;

		if (readers == 1){
			sem_wait(&writeLock);
		}
		sem_post(&readLock);
		printf("Reader reads data[1], Value: %d\n",data[1]);

		sem_wait(&readLock);
		readers--;

		if (readers == 0){
			sem_post(&writeLock);
		}
		sem_post(&readLock);
		
		sleep((int)(drand48()*1000)%5);
	}
	
}




int main(){	

    int i;
    pthread_t thread;



    if(sem_init(&readLock, 0, 1)) { 
		printf("Could not initialize a semaphore\n"); 
		return -1; 
	} 

	if(sem_init(&writeLock, 0, 1)) { 
		printf("Could not initialize a semaphore\n"); 
		return -1; 
	} 

	for (i = 0; i<10; i++){
		if (pthread_create(&thread, NULL, reader, NULL)) { 
			printf("Could not create thread\n"); 
			return -1; 
		} 
	}



	
    while (1){

    	sem_wait(&writeLock);
		int temp = 1;
		data[temp]++;
		printf("Writer writes data[%d], Value: %d\n", temp, data[temp]);
		sem_post(&writeLock);
    	
		sleep((int)(drand48()*1000)%5);
    }

    	printf("%d\n", data[1]);
    

    return 0;
}