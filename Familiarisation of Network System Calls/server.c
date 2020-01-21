#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

void main()
{
    int server_fd, new_socket, value;
    char buffer[2048] = {0};
    int opt = 1;
    int PORT = 3000;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("Socket creation on server failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        printf("Socket binding failed\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0)
    {
        printf("Socket listen failed\n");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        printf("Connection request accept failed\n");
        exit(EXIT_FAILURE);
    }

    value = read(new_socket, buffer, 2048);
    printf("%s\n", buffer);
}