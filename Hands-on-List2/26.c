#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main()
{
    //run 24.c first

    struct mymsg
    {
        long int mtype;
        char msg[100];
    };

    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);
    struct mymsg m1;
    printf("Enter the type of msg:\n");
    scanf("%ld", &(m1.mtype));
    printf("Enter the message:\n");
    fflush(stdout);
    scanf(" %[^\n]", m1.msg);
    int ret = msgsnd(msqid, &m1, sizeof(m1.msg), 0);
    if (ret == -1)
    {
        perror("msgsnd error");
        exit(0);
    }
    printf("Message sent to messageQ successfully\n");
    return 0;
}