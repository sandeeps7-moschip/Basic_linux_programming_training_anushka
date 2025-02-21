Name : Anushka Jagadale
 
Problem statement : 
C program Test problem statement: Develop a railway reservation application system.
Your application should consists of a server and client.
Client will send queries like-
1. Book a ticket
2. View Available seats
3. Print booked ticket
 
Server should process the request at the background and must create a separate thread for each client request.
Server should handle options like book ticket, print ticket, show available number of seats.
Implementation should use linked lists, pointers, file IO, socket programming, multi-threading.
	
Source file path:
	assignments/assesment/src
 
Source file name:
	server1.c
	client1.c
	
 
Build program:
	make
	
 
Run program:
	On server side : 
		gcc server.c -o server
		
	On client side :
		gcc client.c -o client
		

Explanation :
	In this program, client starts reading a text file and sends it to server in 1KB chunks. On receiving each chunk, server converts the text into all capital letter and sends it back to client. Client writes the received data in output file.
