//Anushka Jagadale
//Date : 17/02/2025

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

/* Server side */

/* Header files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <sys/stat.h>
 
#define PORT 8090
#define MAX_SEATS 10
#define MAX_TRAINS 5
 
static long count = 0;
 
typedef struct Ticket {
    int seat_no;
    char passenger_name[50];
    long prn;
    struct Ticket *next;
} Ticket;
 
typedef struct Train {
    int train_no;
    Ticket *head;
    pthread_mutex_t lock;
} Train;
 
Train trains[MAX_TRAINS];
 
void init_trains() {
    for (int i = 0; i < MAX_TRAINS; i++) {
        trains[i].train_no = i + 1;
        trains[i].head = NULL;
        pthread_mutex_init(&trains[i].lock, NULL);
    }
}
 
int add_ticket(int train_no, int seat_no, char *name) {  
    count = count + 1;
    Train *train = &trains[train_no - 1];  
    pthread_mutex_lock(&train->lock);  
 
    Ticket *current = train->head;  
    while (current != NULL) {  
        if (current->seat_no == seat_no) {  
            pthread_mutex_unlock(&train->lock);  
            return 0;  
        }  
        current = current->next;  
    }  
 
    Ticket *new_ticket = (Ticket *)malloc(sizeof(Ticket));  
    new_ticket->seat_no = seat_no;  
    strcpy(new_ticket->passenger_name, name);  
    new_ticket->next = train->head;  
    new_ticket->prn = count;
    train->head = new_ticket;  
 
    pthread_mutex_unlock(&train->lock);  
    return 1;  
}
 
int available_seats(int train_no) {
    Train *train = &trains[train_no - 1];
    int available_seats = MAX_SEATS;
    Ticket *current = train->head;
    while (current != NULL) {
        available_seats--;
        current = current->next;
    }
    return available_seats;
}
 
void print_ticket(int train_no, int prn, char *response) {
    printf("\nIn print function\n");
    Train *train = &trains[train_no - 1];
    Ticket *current = train->head;
    char buffer[1024];
    sprintf(buffer, "%dticket.txt", prn);
    FILE* file = fopen(buffer, "w");
    while (current != NULL) {
        if (current->prn == prn) {
            fprintf(file, "Ticket - Train No: %d, Seat No: %d, Passenger Name: %s PRN : %d\n", train_no, current->seat_no, current->passenger_name, prn);
            printf("Ticket - Train No: %d, Seat No: %d, Passenger Name: %s\n", train_no, current->seat_no, current->passenger_name);
            fclose(file);
            printf("\nReturning from the print function\n");
            return;
        }
        current = current->next;
    }
    sprintf(response, "Ticket not found for train number: %d, PRN number: %d.\n", train_no, prn);
}
 
void save_data() {
    FILE *file = fopen("reservations.txt", "w");
    if (file == NULL) {
        perror("Could not open file");
        return;
    }
    fprintf(file, "Train_no  Seat_no  Passenger_name\n");
    for (int t = 0; t < MAX_TRAINS; t++) {
        Ticket *temp = trains[t].head;
        while (temp) {
            fprintf(file, "%d\t   %d\t   %s\n", trains[t].train_no, temp->seat_no, temp->passenger_name);
            temp = temp->next;
        }
    }
    fclose(file);
}
 
void *handle_client(void *socket_desc) {
    int sock = *(int *)socket_desc;
    int read_size;
    char client_message[2000];
    char response[2000];
    char name[50];
    int train_no, seat_no, p;
 
    while ((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        client_message[read_size] = '\0'; // Null-terminate the received message
        printf("Received from client: %s\n", client_message);
 
        char *command = strtok(client_message, " ");
        if (command == NULL) {
            strcpy(response, "Invalid request\n");
        } else {
            if (strcmp(command, "Booking") == 0) {  
                char *train_str = strtok(NULL, " ");  
                char *seat_str = strtok(NULL, " ");  
                char *name_str = strtok(NULL, " ");  
                char *pnr_str = strtok(NULL, " ");
                if (train_str && seat_str && name_str && sscanf(train_str, "%d", &train_no) == 1 && sscanf(seat_str, "%d", &seat_no) == 1) {  
                    if (train_no > 0 && train_no <= MAX_TRAINS) {  
                        if (add_ticket(train_no, seat_no, name_str)) {  
                            save_data();  
                            sprintf(response, "Ticket booked successfully\n Your PRN number is %ld please save it for further assistance", count);  
                        } else {  
                            strcpy(response, "Seat already booked\n");  
                        }  
                    } else {  
                        strcpy(response, "Invalid train number\n");  
                    }  
                } else {  
                    strcpy(response, "Invalid booking format\n");  
                }  
            } else if (strcmp(command, "Available") == 0) {
                char *train_str = strtok(NULL, " ");
                if (train_str && sscanf(train_str, "%d", &train_no) == 1) {
                    if (train_no > 0 && train_no <= MAX_TRAINS) {
                        sprintf(response, "Available seats in Train No: %d: %d\n", train_no, available_seats(train_no));
                    } else {
                        strcpy(response, "Invalid train number\n");
                    }
                } else {
                    strcpy(response, "Invalid request format\n");
                }
            } else if (strcmp(command, "Print") == 0) {
                char *train_str = strtok(NULL, " ");
                char *pnr_str = strtok(NULL, " ");
                if (sscanf(pnr_str, "%d", &p) == 1 && sscanf(train_str, "%d", &train_no) == 1) {
                    if (train_no > 0 && train_no <= MAX_TRAINS) {
                        print_ticket(train_no, p, response);
                        struct stat file_stat;
                        char buffer[1024];
                        off_t offset = 0;
                        sprintf(buffer, "%dticket.txt", p);
                        int file_fd = open(buffer, O_RDONLY);
                        fstat(file_fd, &file_stat);
                        sendfile(sock, file_fd, &offset, file_stat.st_size);
                        close(file_fd);    
                        printf("\nReturned from the print function\n");
                        sprintf(response, "\nTicket downloaded successfully\n"); 
                    } else {
                        strcpy(response, "Invalid train number\n");
                    }
                } else {
                    strcpy(response, "Invalid print format\n");
                }
            } else {
                strcpy(response, "Invalid request\n");
            }
        }
        write(sock, response, strlen(response));
        memset(client_message, 0, 2000);
        memset(response, 0, 2000);
    }
 
    if (read_size == 0) {
        printf("Client disconnected\n");
    } else if (read_size == -1) {
        perror("recv failed");
    }
 
    free(socket_desc);
    return 0;
}
 
int main() {
    int server_sock, client_sock, c, *new_sock;
    struct sockaddr_in server, client;
 
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        printf("Could not create socket");
    }
    printf("Socket created\n");
 
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
 
    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        return 1;
    }
    printf("Bind done\n");
 
    listen(server_sock, 3);
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
 
    init_trains();
 
    while ((client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&c))) {
        printf("Connection accepted\n");
 
        pthread_t client_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
 
        if (pthread_create(&client_thread, NULL, handle_client, (void *)new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
    }
 
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
 
    for (int i = 0; i < MAX_TRAINS; i++) {
        pthread_mutex_destroy(&trains[i].lock);
    }
 
    return 0;
}

