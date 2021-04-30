#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

/*Zombie process : A process which has fininshed the execution but still has entry in the process table to report to its parent process is known as zombie process. 
A child process always first becomes a zombie before being removed from the process table. The parent process reads the exit status of the child process which reaps off the child process entry from the process table.
*/
int main()
{
    int ret = fork();

    if (!ret) //child process
    {
        printf("Child process id : %d\n", getpid());
        exit(0);
    }
    else
        sleep(50);

    return 0;
}
//ps pid