#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer
{
    long msg_type;
    char text[100];
} message;

void main()
{
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
    printf("Enter data to be written\n");
    scanf("%s", message.text);
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Data sent is: %s\n", message.text);
}