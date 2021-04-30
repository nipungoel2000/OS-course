#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

/*A process whose parent process no more exists i.e. either finished or terminated 
without waiting for its child process to terminate is called an orphan process.
*/

int main()
{
    int ret = fork();

    if (!ret)
    {
        sleep(30);
        printf("In child process, its pid : %d\n", getpid());
    }
    else
    {
        printf("In parent process\n");
    }
    //wait(0);
    return 0;
}