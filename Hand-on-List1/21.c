#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
    int ret = fork();
    if (!ret) //for child process
    {
        printf("printing from child process...\n");
        printf("Child process id : %d\n", getpid());
        printf("Parent process id : %d\n", getppid());
    }
    else //parent process
    {
        printf("printing from parent process...\n");
        printf("Parent process id : %d\n", getpid());
        //printf("%d\n", getppid());
    }
    return 0;
}