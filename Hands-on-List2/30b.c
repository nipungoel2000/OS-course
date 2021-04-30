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
    void *data;
    data = shmat(shmid, NULL, SHM_RDONLY); //0 flag indicates read and write
    printf("Message in shared memory segment(if at all): %s\n", (char *)data);

    printf("Enter the new message: ");
    scanf(" %[^\n]", (char *)data);
    //We receive segmentation fault... because the data pointer cannot be used for writing and so invalid pointer
    return 0;
}