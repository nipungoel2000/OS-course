#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

union semun {
    int val;
    struct semid_ds *buffer;
    unsigned short *array;
};
struct ticket
{
    int cnt;
};

int main()
{
    key_t key = ftok(".", 't');
    int semid;
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0744);

    if (semid != -1) //Creating a semaphore
    {
        printf("Key %d \t Semid: %d\n", key, semid);
        union semun arg;
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
        printf("Semaphore created successfully\n");
        int fd = open("32file.txt", O_RDWR);
        if (fd == -1)
        {
            printf("File open failed\n");
            exit(0);
        }
        struct ticket tkt = {0};
        write(fd, &tkt, sizeof(struct ticket));
        printf("Initialisation of file successful\n");
        close(fd);
    }
    else //Semaphore already exists .. so now access
    {
        semid = semget(key, 1, 0);
        printf("Key %d \t Semid: %d\n", key, semid);
        struct sembuf s = {0, -1, 0};
        struct ticket tkt;

        printf("Locking Semaphore\n");
        semop(semid, &s, 1);
        printf("Inside critical section :----semaphore\n");
        int fd = open("32file.txt", O_RDWR);
        if (fd == -1)
        {
            printf("File open failed\n");
            exit(0);
        }
        read(fd, &tkt, sizeof(struct ticket));
        lseek(fd, 0, SEEK_SET);
        printf("Current ticket count : %d\n", tkt.cnt);
        printf("Enter your ticket count: ");
        int tick;
        scanf("%d", &tick);
        tkt.cnt += tick;
        write(fd, &tkt, sizeof(struct ticket));
        printf("New ticket count : %d\n", tkt.cnt);
        close(fd);
        s.sem_op = 1;
        semop(semid, &s, 1);
        printf("Semaphore unlocked\n");
    }
    return 0;
}