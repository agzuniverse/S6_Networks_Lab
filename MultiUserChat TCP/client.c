#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

char msg[500];

void *recvmg(void *my_sock)
{
    int sock = *((int *)my_sock);
    int len;
    while ((len = recv(sock, msg, 500, 0)) > 0)
    {
        msg[len] = ' ';
        fputs(msg, stdout);
    }
}

int main(int argc, char *argv[])
{
    pthread_t recvt;
    int len;
    int sock;
    char send_msg[500];
    struct sockaddr_in ServerIp;
    char client_name[100];
    strcpy(client_name, argv[1]);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    ServerIp.sin_port = htons(1234);
    ServerIp.sin_family = AF_INET;
    ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ((connect(sock, (struct sockaddr *)&ServerIp, sizeof(ServerIp))) == -1)
        printf("Connection to socket failed\n");

    pthread_create(&recvt, NULL, (void *)recvmg, &sock);

    while (fgets(msg, 500, stdin) > 0)
    {
        strcpy(send_msg, client_name);
        strcat(send_msg, ":");
        strcat(send_msg, msg);
        len = write(sock, send_msg, strlen(send_msg));
        if (len < 0)
            printf("Message not sent\n");
    }
    pthread_join(recvt, NULL);
    close(sock);
    return 0;
}