/*
C program Test problem statement: Develop a railway reservation application system.
Your application should consists of a server and client.
Client will send queries like-
1. Book a ticket
2. View Available seats
3. Print booked ticket
 
Server should process the request at the background and must create a separate thread for each client request.
Server should handle options like book ticket, print ticket, show available number of seats.
Implementation should use linked lists, pointers, file IO, socket programming, multi-threading.
*/

/* Client side */

/* header files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define PORT 8090
 
void communicate_with_server(int sock) {
    char server_reply[2000];
    char client_message[2000];
    char buffer[2000]; 
    while (1) {
        printf("API Menu:\n");
        printf("1. Book a ticket\n");
        printf("2. View Available seats\n");
        printf("3. Print booked ticket\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer
 
        switch (choice) {
            case 1: {
                int train_no, seat_no;
                char passenger_name[50];
                printf("Enter train number: ");
                scanf("%d", &train_no);
                label1:
                    printf("Enter seat number: ");
                    scanf("%d", &seat_no);
                    if(seat_no > 10 || seat_no < 1) {
                        printf("\nInvalid seat no\n");
                        goto label1;
                    }
                getchar(); // Clear the newline character from the input buffer
                printf("Enter passenger name: ");
                fgets(passenger_name, 50, stdin);
                passenger_name[strcspn(passenger_name, "\n")] = '\0'; // Remove the newline character
                sprintf(client_message, "Booking %d %d %s", train_no, seat_no, passenger_name);
                break;
            }
            case 2: {
                int train_no;
                printf("Enter train number: ");
                scanf("%d", &train_no);
                sprintf(client_message, "Available %d", train_no);
                break;
            }
            case 3: {
                int pnr, train_no;
                printf("Enter pnr number: ");
                scanf("%d", &pnr);
                printf("Enter train number: ");
                scanf("%d", &train_no);
                sprintf(client_message, "Print %d %d", train_no, pnr);
                break;
            }
            case 4:
                close(sock);
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }
 
        if (send(sock, client_message, strlen(client_message), 0) < 0) {
            printf("Send failed\n");
            return;
        }
 
        if (client_message[0] == 'P') {
            recv(sock, buffer, sizeof(buffer), 0);
            printf("%s",buffer);
            char new[2000];
            int i = 0;
            while(buffer[i] != '\n') {
            	new[i++] = buffer[i++];
            }
            new[i] = '\0';
            char file[2000];
            printf("Enter a location and file name where you want to save a file: ");
            getchar(); // Clear the newline character from the input buffer
            fgets(file, sizeof(file), stdin);
            file[strcspn(file, "\n")] = '\0'; // Remove the newline character
            FILE *file1 = fopen(file, "w");
            fprintf(file1, "%s", buffer);
            fclose(file1);
            printf("Ticket saved successfully to %s\n", file);
        }
 		
 		if(client_message[0] == 'P') strcpy(server_reply, "Ticket Downloaded Successfully\n");
        if (client_message[0] != 'P' && recv(sock, server_reply, 2000, 0) < 0) {
            printf("Recv failed\n");
            break;
        }
 
        printf("Server reply: %s\n", server_reply);
        memset(client_message, 0, 2000);
        memset(server_reply, 0, 2000);
    }
}
 
int main() {
    int sock;
    struct sockaddr_in server;
 
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket\n");
    }
    printf("Socket created\n");
 
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
 
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
 
    printf("Connected to server\n");
 
    communicate_with_server(sock);
 
    close(sock);
    return 0;
}

