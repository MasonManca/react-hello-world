/**
 * Mason Manca
 * CPSC 346 Sec. 02
 * Dr.Zhang
 * Project 5
 * Nov. 2 2022
 */

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TRUE 1


buffer_item buffer[BUFFER_SIZE];
/*define semaphores and mutex*/
sem_t empty;
sem_t occupied;

pthread_mutex_t buffer_mutex;

int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
    /* Acquire Empty Semaphore */
	sem_wait(&empty);
	
	/* Acquire mutex lock to protect buffer */
	pthread_mutex_lock(&buffer_mutex);


	/* Release mutex lock and full semaphore */
	buffer[insertPointer] = item;
	if(++insertPointer >= BUFFER_SIZE){
		insertPointer = 0;
	}

	pthread_mutex_unlock(&buffer_mutex);
	sem_post(&occupied);

	return 0;
}

int remove_item(buffer_item *item)
{
	/* Acquire Full Semaphore */
	sem_wait(&empty);

	/* Acquire mutex lock to protect buffer */
	pthread_mutex_lock(&buffer_mutex);

	/* Release mutex lock and empty semaphore */
	 	*item = buffer[removePointer];
	if(++removePointer >= BUFFER_SIZE)
		removePointer = 0;

	/* Release mutex lock and empty semaphore */
	pthread_mutex_unlock(&buffer_mutex);
	sem_post(&empty);

	return 0;
}


int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	if(argc != 4)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	/*call atoi to get arguments */
	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);
 
	/* Create the producer and consumer threads */
	pthread_t producers[producerThreads];
	pthread_t consumers[consumerThreads];

	if(pthread_mutex_init(&buffer_mutex, 0) != 0){
		printf("Mutex error, initialization failed\n");
		return -1;
	}

	if(sem_init(&empty, 0, BUFFER_SIZE) != 0 || sem_init(&occupied, 0, 0) != 0){
		printf("Semaphore error, initialization failed\n");
		return -1;
	}

	for(i = 0; i < producerThreads; i++){
		pthread_create(&producers[i], 0, producer, NULL);
	}

	for(j = 0; j < consumerThreads; j++)
	{
		pthread_create(&consumers[j], 0, consumer, NULL);
	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	

	while(producerThreads > 0){
		pthread_join(producers[--producerThreads], NULL);
	}
	while(consumerThreads > 0){
		pthread_join(consumers[--consumerThreads], NULL);
	}
	pthread_mutex_destroy(&buffer_mutex);

	sem_destroy(&empty);
	sem_destroy(&occupied);

	return 0;
}

void *producer(void *param)
{
	buffer_item item;

	while(TRUE)
	{
		sleep(rand() % 10);

		item = rand() % 100;
		if(insert_item(item)){
			printf("error generated, producer condition");
		}
		else{
			printf("producer created %d\n", item);
		}
		pthread_exit(0);

	}

}

void *consumer(void *param)
{
	 
	while(TRUE)
	{
		buffer_item item;

		while(TRUE){
			sleep(rand() % 10);
			if(remove_item(&item)){
				printf("error generated, consumer condition\n");
			}
			else{
				printf("consumer consumed %d\n", item);
			}
		}
	}
	pthread_exit(0);
}