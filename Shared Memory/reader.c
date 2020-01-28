#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Data read from memory is:%s\n", str);
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
}