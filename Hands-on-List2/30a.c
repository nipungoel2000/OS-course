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
    int shmid = shmget(key, 1024, IPC_CREAT | 0777);
    printf("Key : %d \t Shmid: %d\n", key, shmid);
    void *data;
    data = shmat(shmid, NULL, 0); //0 flag indicates read and write
    printf("Enter the message: ");
    scanf(" %[^\n]", (char *)data);
    return 0;
}