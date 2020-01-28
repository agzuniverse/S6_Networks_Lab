#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MSGSIZE 16

char *msg1 = "Message 1";
char *msg2 = "Message 2";

void main()
{
    char inbuf[MSGSIZE];
    int p[2];

    if (pipe(p) < 0)
        exit(1);

    write(p[1], msg1, MSGSIZE);
    write(p[1], msg2, MSGSIZE);

    for (int i = 0; i < 3; i++)
    {
        read(p[0], inbuf, MSGSIZE);
        printf("%s\n", inbuf);
    }
}
