#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//ls -l | grep ^d | wc  using dup2

int main()
{
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    int ret = fork();
    if (ret > 0) //parent
    {
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
        dup2(fd1[0], 0);
        execlp("wc", "wc", NULL);
    }
    else
    {
        int ret2 = fork();
        if (ret2 > 0) //child
        {
            close(fd2[1]);
            close(fd1[0]);
            dup2(fd2[0], 0);
            dup2(fd1[1], 1);
            execlp("grep", "grep", "^d", NULL);
        }
        else //child of child
        {
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);   //closing read end
            dup2(fd2[1], 1); //making STDOUT same as fd2[1]
            execlp("ls", "ls", "-l", NULL);
        }
    }
    return 0;
}