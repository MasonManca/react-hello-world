/**
 * Mason Manca
 * CPSC 346 Sec. 2
 * Dr. Zhang
 * Oct 21 2022
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE				10
#define NUMBER_OF_THREADS	3

void *sorter(void *params);	/* thread that performs basic sorting algorithm */
void *merger(void *params);	/* thread that performs merging of results */

int list[SIZE] = {7,12,19,3,18,4,2,6,15,8};

int result[SIZE];

typedef struct
{
	int from_index;
	int to_index;
} parameters;

int main (int argc, const char * argv[]) 
{    
	pthread_t workers[NUMBER_OF_THREADS];
	
	//print unsorted array
	printf("Unsorted array:\n");
	for (int i = 0; i < SIZE; i++) {
		printf("%d\t", list[i]);
	}
	printf("\n");

	/* establish the first sorting thread */
	//1. call malloc to allocate a “parameters”
	parameters *threadParameters = (parameters *) malloc (sizeof(parameters));
	//2. use “parameters” to specify the first half of the array
	threadParameters->from_index = 0;
	threadParameters->to_index = (SIZE/2) - 1;
   	//3. create the first thread
	pthread_create(&workers[0], 0, sorter, threadParameters);

	/* establish the second sorting thread */
	//1. call malloc to allocate a “parameters”  	 
	//2. use “parameters” to specify the second half of the array
	//3. create the second thread
	threadParameters = (parameters *) malloc (sizeof(parameters));
	
	threadParameters->from_index = SIZE/2;
	threadParameters->to_index = SIZE - 1;

	pthread_create(&workers[1], 0, sorter, threadParameters);
	
	/* now wait for the 2 sorting threads to finish */
	// use pthread_join; wait for 2 sorting threads to finish 
	pthread_join(workers[0],NULL);
	pthread_join(workers[1],NULL);

	/* establish the merge thread */
	//reuse “parameters” to hold the beginning index in each half
	//from_index is start of first, to_index is start of second
	threadParameters->from_index = 0;
	threadParameters->to_index = SIZE/2;

	//create the third thread: merge 
	pthread_create(&workers[2], 0, merger, threadParameters);
	
	// wait for the merge thread to finish 
	 pthread_join(workers[2], NULL);

	/* output the sorted array */
	printf("Sorted array:\n");
	for (int i = 0; i < SIZE; i++) {
		printf("%d\t", result[i]);
	}
	printf("\n");

    return 0;
}
/*
 * Swap function
 * takes in two values and swaps them by dereferencing pointers
*/
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


/**
 * Sorting thread.
 * Used selection sort, as it is the easiest sorting algorithm
*/
void *sorter(void *params)
{
	parameters* p = (parameters *)params;
	int start = p->from_index;
	int pSize = p->to_index + 1;
	
	// finds smallest value and swaps it with the first value in the unsorted part of the thread
	for (int i = start; i < pSize - 1; i++) {
		int min = i;
		for (int j = i + 1; j < pSize; j++) {
			if(list[j] < list[min])
				min = j;
		}
		swap(&list[min], &list[i]);
	}
	pthread_exit(0);
}


/**
 * Merge thread, recieved pointer of parameters and merges the values in the threads
 * Using simple merge sort for merging two sublists
 */
void *merger(void *params)
{
	parameters* p = (parameters *)params;
	
	//reuse “parameters” to hold the first index in each half
	//merge two sorted sublists to the arry result
	int firstHalfOfArray = p->from_index;
	int secondHalfOfArray = p->to_index;
	int i = 0;

	// iterate through both arrays
	while ((firstHalfOfArray < p->to_index) && (secondHalfOfArray < SIZE)) {
		// compare smallest values, insert small in first half if < second half value
		if (list[firstHalfOfArray] < list[secondHalfOfArray]) {
			result[i] = list[firstHalfOfArray];
			++firstHalfOfArray;
		}
		// first value in second half is smaller than first in first half
		else {
			result[i] = list[secondHalfOfArray];
			++secondHalfOfArray;
		}
		++i;
	}
	// append last values of first half since they are smaller
	while (firstHalfOfArray < p->to_index) {
		result[i] = list[firstHalfOfArray];
		++firstHalfOfArray;
		++i;
	}
	// append last values of second half since they are smaller
	while (secondHalfOfArray < SIZE) {
		result[i] = list[secondHalfOfArray];
		++secondHalfOfArray;
		++i;
	}

	pthread_exit(0);
}