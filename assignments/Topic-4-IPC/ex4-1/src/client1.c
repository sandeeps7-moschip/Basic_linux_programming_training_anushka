/*
Write down a TCP client-server application which meets following requirements:
-   Both server and clients are separate applications written in separate source files
-   Server application takes IP address of interface and port address to listen on as command line arguments
-   Client application takes IP address of server to connect as command line argument
-   Server allows multiple connection simultaneously by spawning separate request handler thread for each client
-   On, successful connection establishment client starts reading a text file and sends it to server in 1KB chunks. On receiving each chunk, server converts the text into all capital letter and sends it back to client. Client writes the received data in output file. When whole file is converted to capital letters, client exits gracefully by closing the connection. On this event, the request handler thread on server for the client also terminates gracefully.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[1024];

   /* Checks the argumnet count is less than 4 or not */
    if (argc < 4) {
        fprintf(stderr,"usage %s hostname port inputfile\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  /* Create a socket */
    if (sockfd < 0) {
        error("Error opening socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Error, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));  /* set all bytes in a block of memory to zero */
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Connection with server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed");
    }
    

    FILE *infile = fopen("../data/input.txt", "r");  /* Open file input.txt in read mode */
    if (infile == NULL) {   /* Validation */
        error("Error opening input file");
    }

    FILE *outfile = fopen("../data/output.txt", "w");  /* Open file output.txt in write mode */
    if (outfile == NULL) {  /* Validation */
        error("Error opening output file");
    }

    while (fgets(buffer, 1024, infile) != NULL) {
        n = write(sockfd, buffer, strlen(buffer));  
        if (n < 0) {
            error("Error writing to socket");
        }

        bzero(buffer, 1024);
        n = read(sockfd, buffer, 1024);
        if (n < 0) {
            error("Error reading from socket");
        }

        fputs(buffer, outfile);
    }

    fclose(infile);
    fclose(outfile);
    close(sockfd);
    return 0;
}

