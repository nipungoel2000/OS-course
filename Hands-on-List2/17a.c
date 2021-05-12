#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//ls -l | wc  using dup

int main()
{
    int fd[2];
    pipe(fd);

    int ret = fork();
    if (ret > 0) //parent process
    {
        // wait(0);
        close(fd[1]); //close write end
        close(0);     //closing normal stdin
        dup(fd[0]);   //making STDIN same as fd[0]
        execlp("wc", "wc", NULL);
    }
    else
    {
        close(fd[0]); //close read end
        close(1);     //closing normal stdout
        dup(fd[1]);   //making STDOUT same as fd[1]
        execlp("ls", "ls", "-l", NULL);
    }
}