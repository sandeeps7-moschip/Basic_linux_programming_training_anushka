
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
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

/* Covert into uppercase */
void convert_to_uppercase(char *buffer) {
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = toupper(buffer[i]);
    }
}

/* Function to handel multiple client */
void *handle_client(void *client_sockfd) {
    int sockfd = *(int *)client_sockfd;
    char buffer[1024];
    int n;

    while (1) {
        bzero(buffer, 1024);  /* to set buffer memory zero */
        n = read(sockfd, buffer, 1023);   /* Read data from buffer */
        if (n < 0) {
            error("Error reading from socket");
        }

        if (strncmp("Bye", buffer, 3) == 0) {
            break;
        }

        convert_to_uppercase(buffer);  /* Convert buffer data into uppercase */

        n = write(sockfd, buffer, strlen(buffer));  /* Modified data write into buffer */
        if (n < 0) {
            error("Error writing to socket");
        }
    }

    close(sockfd);
    free(client_sockfd);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* Checks the argument count is less than 2 or not */
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);   /* Create socket */
    if (sockfd < 0) {
        error("Error opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); /* set all bytes in a block of memory to zero */
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Associate local address with socket */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Error on binding");
    }

    listen(sockfd, 5);  /* to accept connection */
    clilen = sizeof(cli_addr);

    while (1) {
        /* Accepts connection from client & return new socket i.e. newsockfd */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            error("Error on accept");
        }

        int *client_sockfd = malloc(sizeof(int));
        *client_sockfd = newsockfd;

        pthread_t thread_id;  /* declare thread variable */
        if (pthread_create(&thread_id, NULL, handle_client, (void *)client_sockfd) < 0) {   /* Create a thread */
            error("Error creating thread");
        }

        pthread_detach(thread_id);   /* Thread detach function */
    }

    close(sockfd);
    return 0;
}

