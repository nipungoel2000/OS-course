#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main()
{
    /* If wait for pid2 is removed then the parent process 
    waits only for pid1 and therefore pid2 becomes orphan*/
    int pid1, pid2, pid3;

    pid1 = fork();
    if (!pid1)
    {
        sleep(1);
        printf("First child with pid %d and parent pid %d\n ", getpid(), getppid());
    }
    else
    {
        pid2 = fork();
        if (!pid2)
        {
            sleep(2);
            printf("Second child with pid %d and parent pid %d\n ", getpid(), getppid());
        }
        else
        {
            pid3 = fork();
            if (!pid3)
            {
                printf("Third child with pid %d and parent pid %d\n ", getpid(), getppid());
            }
        }
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    //printf("test\n");
    //  printf("%d %d %d \n", pid1, pid2, pid3);
    return 0;
}