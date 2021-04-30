#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// struct sembuf
// {
//     short sem_num;
//     short sem_op;
//     short sem_flg;
// };
/*The first member of the structure
indicates the particular semaphore in
the set; in this case, it is the first
semaphore. The second member
indicates that the value of the
semaphore is decrementing, and the
third member determines as what the
semop function will do if the
semaphore is busy.*/
int main()
{
    key_t key = ftok(".", 'c');
    int semid = semget(key, 1, 0);
    struct sembuf buf = {0, -1, 0};

    printf("Before locking...\n");
    semop(semid, &buf, 1);
    printf("Inside critical section...\n");
    printf("Press Enter to Unlock\n");
    getchar();
    buf.sem_op = 1;
    semop(semid, &buf, 1);
    printf("Unlocked\n");
    return 0;
}