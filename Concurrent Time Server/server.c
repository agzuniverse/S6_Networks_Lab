/*
Implement Concurrent Time Server application using UDP to execute the program at remote server.
Client sends a time request to the server, server sends its system time back to the client. Client
displays the result.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
  int sockfd;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr, cliaddr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  servaddr.sin_family = AF_INET; // IPv4 
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  if (bind(sockfd, (const struct sockaddr *)&servaddr,
      sizeof(servaddr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  int len, n;

  len = sizeof(cliaddr); 
  while(1){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
        MSG_WAITALL, (struct sockaddr *)&cliaddr,&len);
    buffer[n] = '\0';
    time_t t;
    time(&t);
    char *server_time = ctime(&t);
    sendto(sockfd, (const char *) server_time, strlen(server_time),
        MSG_CONFIRM, (const struct sockaddr * ) & cliaddr,
        len);
    printf("Time sent to client.\n");
  }
  return 0;
}