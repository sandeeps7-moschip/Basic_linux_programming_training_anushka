Name : Anushka Jagadale
 
Problem statement : 
Write down a TCP client-server application which meets following requirements:
-   Both server and clients are separate applications written in separate source files
-   Server application takes IP address of interface and port address to listen on as command line arguments
-   Client application takes IP address of server to connect as command line argument
-   Server allows multiple connection simultaneously by spawning separate request handler thread for each client
-   On, successful connection establishment client starts reading a text file and sends it to server in 1KB chunks. On receiving each chunk, server converts the text into all capital letter and sends it back to client. Client writes the received data in output file. When whole file is converted to capital letters, client exits gracefully by closing the connection. On this event, the request handler thread on server for the client also terminates gracefully.
	
Source file path:
	assignments/Topic-4-IPC/ex4-1/src
	assignments/Topic-4-IPC/ex4-1/data
 
Source file name:
	server1.c
	client1.c
	input.txt
 
Build program:
	make
	
 
Run program:
	On server side : 
		gcc server1.c -o server1
		./server 9850(port no)
	On client side :
		gcc client1.c -o client1
		./client localhost 9850 input.txt

Explanation :
	In this program, client starts reading a text file and sends it to server in 1KB chunks. On receiving each chunk, server converts the text into all capital letter and sends it back to client. Client writes the received data in output file.
