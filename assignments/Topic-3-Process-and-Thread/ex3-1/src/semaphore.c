/* 
Write down a simple multiple threaded application with two threads. Each thread increments common global variable for N time.
   Choose value of N such large that the program demonstrates race condition between two threads.
   Now, modify the program to avoid race condition by using mutex.
   Again modify the program to avoid race condition by using semaphores.
*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

/* global variabel */
int global_var = 0;
sem_t semaphore; /* Semaphore variable declaration */

/* Macro defination */
#define N 200000

/* Function declaration */
void* increment(void* args);

/* main function */
int main() {
	
	pthread_t thread1, thread2; /* thread declaration */
	
	sem_init(&semaphore, 0, 1); /* semaphore initialization, 0 - no.of process, 1 - no of thread */

	/* thread creation */
	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, increment, NULL);

	/* thread joining */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	sem_destroy(&semaphore); /*clean-up the semaphore */
	
	printf("\nFinal value of the global variable is : %d\n",global_var);
	return 0;
}

/* Thread function */
void* increment(void* args) {
	sem_wait(&semaphore); /* Wait, decrements the semaphore value */
	for(int i = 0; i < N; i++) {
		global_var++;
	}
	sem_post(&semaphore); /* Post, increments the semaphore value */	
	return NULL;
}
	

