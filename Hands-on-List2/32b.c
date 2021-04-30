#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok(".", 'c');
    int semid = semget(key, 1, 0);
    struct sembuf buf = {0, -1, 0};
    printf("Key : %d \t Semid: %d\n", key, semid);
    key_t key1 = ftok(".", 'a');
    int shmid = shmget(key1, 1024, IPC_CREAT | 0744);
    printf("Key : %d \t Shmid: %d\n", key1, shmid);

    printf("Before locking...\n");
    semop(semid, &buf, 1);

    printf("Inside critical section...\n");
    printf("Press Enter to Unlock and write to shared memory\n");
    getchar();

    buf.sem_op = 1;
    semop(semid, &buf, 1);
    printf("Unlocked\n");

    void *data;
    data = shmat(shmid, NULL, 0); //0 flag indicates read and write
    printf("Enter the message: ");
    scanf(" %[^\n]", (char *)data);

    return 0;
}