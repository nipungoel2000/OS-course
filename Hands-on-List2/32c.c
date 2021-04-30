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
    key_t key = ftok(".", 'b');
    int semid;
    semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0744);

    if (semid != -1) //Creating a semaphore
    {
        printf("Key %d \t Semid: %d\n", key, semid);
        static unsigned short semarr[2] = {2, 3};
        union semun arg;
        arg.array = semarr;
        semctl(semid, 0, SETALL, arg);
        for (int i = 0; i < 2; i++)
        {
            int ret = semctl(semid, i, GETVAL, 0);
            printf("sem %d = %d\n", i, ret);
        }
    }
    else //Semaphore already exists .. so now access
    {
        semid = semget(key, 2, 0);
        printf("Key %d \t Semid: %d\n", key, semid);
        struct sembuf s[2] = {{0, -1, 0 | SEM_UNDO}, {1, -1, 0 | SEM_UNDO}};

        printf("Locking Semaphore1\n");
        semop(semid, &s[0], 1);
        printf("Inside critical section :----semaphore1\n");
        printf("ENTER to unlock semaphore1\n");
        getchar();
        s[0].sem_op = 1;
        semop(semid, &s[0], 1);
        printf("semaphore1 unlocked\n");

        printf("Locking Semaphore2\n");
        semop(semid, &s[1], 1);
        printf("Inside critical section :----semaphore2\n");
        printf("ENTER to unlock semaphore2\n");
        getchar();
        s[1].sem_op = 1;
        semop(semid, &s[1], 1);
        printf("semaphore2 unlocked\n");
    }
    return 0;
}