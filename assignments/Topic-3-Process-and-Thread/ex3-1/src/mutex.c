/*
Write down a simple multiple threaded application with two threads. Each thread increments common global variable for N time.
   Choose value of N such large that the program demonstrates race condition between two threads.
   Now, modify the program to avoid race condition by using mutex.
   Again modify the program to avoid race condition by using semaphores.
*/

#include<stdio.h>
#include<pthread.h>

/* Macro defination */
#define N 200000

/* Global variable */
int global_var = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/* Declaration of mutex variable */

/* Function declaration */
void* increment(void* args);

/* Main function */
int main() {

	pthread_t thread1, thread2; /* Thread initialization */
	
	/* Thread creation */
	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, increment, NULL);
	
	
	
	/* Thread joining */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	pthread_mutex_destroy(&mutex); /* destorying mutex */

	printf("\nFinal Value of the global variable is : %d\n", global_var);
	return 0;
}

/* Thread function */
void* increment(void* args) {

	pthread_mutex_lock(&mutex);
	/* Loop until N */
	for(int i = 0; i < N; i++) {
		global_var++;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

