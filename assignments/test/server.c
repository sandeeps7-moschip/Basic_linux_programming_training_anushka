#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<arpa/inet.h>

#define PORT 8080
#define SIZE 10

typedef struct Passenger {
	int PNR;
	char name[20];
	int age;
	struct Passenger *next;
}Passenger;
Passenger *head = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void save() {
	FILE *file = fopen("output.txt","w");
	Passenger *temp = head;
	while(temp != NULL) {
		fprintf(file,"%d %s %d\n",temp -> PNR, temp -> name, temp -> age);
		temp = temp -> next;
	}
	fclose(file);
}
void Print() {
	if(head == NULL) {
		printf("\n Not data");
	}
	Passenger *temp = head;
        while(temp != NULL) {
		printf("%d,%s,%d",temp -> PNR, temp -> name, temp -> age);
		temp = temp -> next;
	}

}	
void BookTicket(int PNR,char name[20],int age) {
	int count = 0;
	
	if(count < SIZE) {
		Passenger* new = malloc(sizeof(Passenger));

		new -> PNR = PNR;
		strcpy(new -> name,name);
		new -> age = age;
		new -> next = NULL;
		if(head == NULL) {
			head = new;
			count++;
		}
		else {
			Passenger* temp = head;
			while(temp -> next != NULL) {
				temp = temp -> next;
			}
			temp -> next = new;
			count++;
		}
	}
}
int Available_seats() { 
	int count = 0;
	if(head == NULL) {
		printf("\nNo booking");
		printf("%d",count);
	}
	Passenger* temp = head;
	while(temp != NULL) {
		temp = temp -> next;
		count++;
	}
	int seats = SIZE - count;
	return seats;

}

void* handle_client(void* args) {
	int client = *(int *)args;
	free(args);
	char buffer[1024];
	char name[20];
	int age;
	int PNR;
	int choice;
	while(1) {
		printf("\nTrain Options: ");
		printf("\n 1.BookTicket\n 2.Available_seats\n 3.Save\n 4.Print\n 5.Exit\n");
		
		scanf("%d",&choice);
		switch(choice) {
			case 1 :
				pthread_mutex_lock(&mutex);

				printf("\nEnter PNR number: ");
			        scanf("%d",&PNR);
       				printf("\nEnter name: ");
   				scanf("%s",name);
      				printf("\nEnter age: ");
     				scanf("%d",&age);

				
				BookTicket(PNR,name,age);
				pthread_mutex_unlock(&mutex);
			       	break;
			case 2 :
			       int seats = Available_seats();
			       printf("Available seats are: %d",seats);
		       	       break;
			case 3 :
				save();
				break;
			case 4 :
			       	Print();
			       	break;
			case 5 :
				exit(0);
				break;

			default:
				 printf("\nInvalid choice");
		}
	}
	close(client);
	return NULL;
}

int main() {
	int server,*client;
	struct sockaddr_in server_addr,client_addr;
	socklen_t client_size = sizeof(client_addr);

	server = socket(AF_INET,SOCK_STREAM,0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	
	bind(server,(struct sockaddr *)&server_addr,sizeof(server_addr));
	listen(server,2);

	while(1) {
		client = malloc(sizeof(int));
		*client = accept(server,(struct sockaddr *)&client_addr,&client_size);

		pthread_t client1;
		pthread_create(&client1,NULL,handle_client,client);
		pthread_detach(client1);

		pthread_t client2;
		pthread_create(&client2,NULL,handle_client,client);
		pthread_detach(client2);
	}
	close(server);
	return 0;
}
