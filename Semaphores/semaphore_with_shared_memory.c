#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <pthread.h>

sem_t readlock, writelock;
int counter;
int shmid;

void *writer(void *arg)
{
    sem_wait(&writelock);
    printf("Writer is in critical section\n");
    char *str = (char *)shmat(shmid, (void *)0, 0);
    sprintf(str, "%d", (int)arg);
    printf("Data written in memory is:%d\n", (int)arg);
    shmdt(str);
    sem_post(&writelock);
}

void *reader(void *arg)
{
    sem_wait(&readlock);
    counter++;
    if (counter == 1)
        sem_wait(&writelock);
    sem_post(&readlock);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Data read from memory is:%s\n", str);
    shmdt(str);
    sem_wait(&readlock);
    counter--;
    if (counter == 0)
        sem_post(&writelock);
    sem_post(&readlock);
}

void main()
{
    sem_init(&readlock, 0, 1);
    sem_init(&writelock, 0, 1);
    key_t key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    pthread_t t1[5], t2[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&t1[i], NULL, writer, (void *)i);
        pthread_create(&t2[i], NULL, reader, (void *)i);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(t1[i], NULL);
        pthread_join(t2[i], NULL);
    }

    shmctl(shmid, IPC_RMID, NULL);
    sem_destroy(&readlock);
    sem_destroy(&writelock);
}