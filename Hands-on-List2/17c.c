#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//ls -l | wc  using fcntl

int main()
{
    int fd[2];
    pipe(fd);
    int ret = fork();
    if (ret > 0) //parent process
    {
        // wait(0);
        close(fd[1]);          //close write end
        close(0);              //closing normal stdin
        fcntl(fd[0], F_DUPFD); //making STDIN same as fd[0]
        execlp("wc", "wc", NULL);
    }
    else
    {
        close(fd[0]);          //close read end
        close(1);              //closing normal stdout
        fcntl(fd[1], F_DUPFD); //making STDOUT same as fd[1]
        execlp("ls", "ls", "-l", NULL);
    }
    return 0;
}