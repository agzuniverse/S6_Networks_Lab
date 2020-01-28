
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    char arr1[80], arr2[80];

    while (1)
    {
        fd = open(myfifo, O_WRONLY);
        printf("Enter message: ");
        scanf("%s", arr2);
        write(fd, arr2, strlen(arr2) + 1);
        close(fd);
        fd = open(myfifo, O_RDONLY);
        read(fd, arr1, sizeof(arr1));
        printf("User2: %s\n", arr1);
        close(fd);
    }
}
