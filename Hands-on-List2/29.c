#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main()
{
    key_t key = ftok(",", 'a');
    int mqid = msgget(key, IPC_CREAT);

    if (msgctl(mqid, IPC_RMID, NULL) == -1)
    {
        perror("Error in removing..\n");
        exit(0);
    }
    printf("Message with mqid : %d removed.\n", mqid);
    return 0;
}