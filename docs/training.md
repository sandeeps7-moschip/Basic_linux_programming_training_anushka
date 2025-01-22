# Overview
## Resources
 - Software
    - GNU C Compiler (GCC) on Linux
    - Doxygen
- Hardware
	- X86 based system with linux installed.
 - Materials
    - Go to [this](./materials/) directory.
## Prerequisites
 - Familiarity with C Programming

## Timelines
| Topic #| Topic | Timeline(in days)|
| :---: | :---: | :---: |
| 1 | Introduction to Linux | 0.25 |
| 2 | Linux programming environment | 1 |
| 3 | Processes and Threads | 1 |
| 4 | Interprocess Communication (IPC) | 2 |
| 5 | Memory Management | 1 |
| 6 | Scheduling in Linux | 1 |
| 7 | Embedded Linux | 1 |
| 8 | Embedded Storage | 1 |                                                                                              | :---: | :---: | :---: |
| | | 8.25 days |


# 1. Introduction to Linux
## Objective
Get an overview of Linux OS and some of the basic commands
## Task
 - Go through Chapter 1, 2, 3.1 and 3.2 of [Intro-Linux](./materials/Intro-Linux.pdf) Book
 - Go through contents provided in below links:
	 - https://www.funtoo.org/Linux_Fundamentals,_Part_1
	-   https://www.funtoo.org/Linux_Fundamentals,_Part_2
	-   https://www.funtoo.org/Linux_Fundamentals,_Part_3
	-   https://www.funtoo.org/Linux_Fundamentals,_Part_4
## Assignment
 None

# 2. Linux programming environment
## Objective
Get overview of GNU make and GNU debugger (gdb), learn how to create static libraries and shared libraries, learn about command line parsing mechanism under Linux.
## Tasks
 - Go through Chapter 1 & 2 of [Advanced Linux Programming](./materials/Advanced_linux_programming.pdf) book.
## Assignment
None

# 3. Processes and Threads
## Objective
Learn about processes and threads, how to create process and threads, difference between process and threads
## Tasks
- Go through Chapter 3 & 4 of [Advanced Linux Programming](./materials/Advanced_linux_programming.pdf) book.
# Assignment
Write down a simple multiple threaded application with two threads. Each thread increments common global variable for N times. Choose value of N such large that the program demonstrates race condition between two threads. Now, modify the program to avoid race condition by using mutex. Again modify the program to avoid race condition by using semaphores.

# 4. Interprocess Communication (IPC)
## Objective
Learn IPC mechanisms - semaphores and mutex, Learn socket programming.
## Task
Go through Chapter 5 of [Advanced Linux Programming](./materials/Advanced_linux_programming.pdf) book.
## Assignment
Write down a TCP client-server application which meets following requirements:
-   Both server and clients are separate applications written in separate source files
-   Server application takes IP address of interface and port address to listen on as command line arguments
-   Client application takes IP address of server to connect as command line argument
-   Server allows multiple connection simultaneously by spawning separate request handler thread for each client
-   On, successful connection establishment client starts reading a text file and sends it to server in 1KB chunks. On receiving each chunk, server converts the text into all capital letter and sends it back to client. Client writes the received data in output file. When whole file is converted to capital letters, client exits gracefully by closing the connection. On this event, the request handler thread on server for the client also terminates gracefully.

# 5. Memory Management
## Objective
Learn about the memory management in the linux. Familiar with the terminology related to memory management.
## Task
Go through the presentation [Memory_management-1.pdf](./materials/Memory_management-1.pdf), [Memory_management-2.pdf](./materials/Memory_management-2.pdf) and [Memory_management-3.pdf](./materials/Memory_management-3.pdf)
## Assignment
None

# 6. Scheduling in Linux
## Objective
Learn about the scheduling in the linux.
## Task
-   Go through the below materials:
	-  [Linux-scheduling-1.pdf](./materials/Linux-scheduling-1.pdf)
	-  [Linux-scheduling-2.pdf](./materials/Linux-scheduling-2.pdf)
	-  [Linux-scheduling-3.pdf](./materials/Linux-scheduling-3.pdf)
## Assignment
None

# 7. Embedded Linux
## Objective
Get an idea about Linux as an embedded operating system, Learn basics of bootloader and kernel, Learn characteristics of RTOS
## Task
Go through Chapter 1, 2 & 7 of [Embedded Linux System Design and Development](./materials/Embedded_Linux_SDD.pdf)
## Assignment
None

# 8. Embedded Storage
## Objective
Learn about storage devices, Learn about Linux kernel support for storage devices, Learn about different filesystem types supported under Linux.
## Task
Go through Chapter 4 of [Embedded Linux System Design and Development](./materials/Embedded_Linux_SDD.pdf)
## Assignment
None


# Evaluation
- Assignments
- One session will be arranged to evaluate the knowledge of the candidate on the above topics. Presentation is not necessary for the same. This will be interactive session where QA will be done at the end.
