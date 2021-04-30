#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
union semun {
    int val;
    struct semid_ds *buffer;
    unsigned short *array;
};
int main()
{
    union semun arg;
    key_t key = ftok(".", 'c');
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0744);
    printf("Key %d \t Semid: %d\n", key, semid);

    arg.val = 2; //Means counting semaphore

    semctl(semid, 0, SETVAL, arg);
    return 0;
}