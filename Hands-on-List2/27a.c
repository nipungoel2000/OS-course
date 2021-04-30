#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main()
{
    struct mymsg
    {
        long int mtype;
        char msg[100];
    };

    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);
    struct mymsg m1;

    printf("Enter the message type: ");
    long int msgtype;
    scanf("%ld", &msgtype);
    int ret = msgrcv(msqid, &m1, sizeof(m1.msg), msgtype, 0);
    if (ret == -1)
    {
        perror("msgrecv error");
        exit(0);
    }
    printf("Message: %s\n", m1.msg);
    return 0;
}