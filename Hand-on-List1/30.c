#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>

int main()
{
    if (!fork())
    {
        printf("child pid : %d\n", getpid());
        setsid();
        chdir("/");
        umask(0);
        while (1)
        {
            sleep(5);
            printf("this is Daemon Process \n");
        }
    }
    else
        exit(0);
}
