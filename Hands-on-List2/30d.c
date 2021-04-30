#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
/*If shmaddr is NULL, the system chooses a suitable (unused)
         page-aligned address to attach the segment.*/
int main()
{
    key_t key = ftok(".", 'a');
    int shmid = shmget(key, 1024, 0);
    printf("Key : %d \t Shmid: %d\n", key, shmid);

    int ret = shmctl(shmid, IPC_RMID, NULL);
    if (ret == -1)
    {
        perror("Cannot remove shared memory segment");
        exit(0);
    }
    printf("Destroyed shared memory\n");
    return 0;
}