#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8080

int main() {
	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

	if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) > 0) {
		printf("\nConnection failed");
	}

	char buffer[1024];
	send(sockfd,buffer,strlen(buffer),0);
	recv(sockfd,buffer,sizeof(buffer),0);
	close(sockfd);
	return 0;
}
