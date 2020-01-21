#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void main()
{
    int client_fd;
    int PORT = 3000;
    char buffer[1024] = {0};
    struct sockaddr_in server;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error creating client socket\n");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0)
    {
        printf("Invalid address\n");
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connection failed\n");
        exit(EXIT_FAILURE);
    }

    char *msg = "This message is from client";
    send(client_fd, msg, strlen(msg), 0);
}