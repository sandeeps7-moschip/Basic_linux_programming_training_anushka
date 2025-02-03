Name : Anushka Jagadale
 
Problem statement : 
Write down a simple multiple threaded application with two threads. Each thread increments common global variable for N time.
Choose value of N such large that the program demonstrates race condition between two threads.
Now, modify the program to avoid race condition by using mutex.
Again modify the program to avoid race condition by using semaphores. 
	
Source file path:
	assignments/Topic-3-Process-and-thread/ex3-1/src
 
Source file name:
	race_condition.c
	mutex.c
	semaphore.c
 
Build program:
	make
	
 
Run program:
	./ex5-1
	OR
	./a.out

Explanation :
	In this program, race condition handled by using mutex and semaphore.
