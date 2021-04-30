#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY);
    int ret = fork();
    if (!ret)
    {
        write(fd, "Writing from Child Process\n", 27);
    }
    else
    {
        write(fd, "Writing from Parent Process\n", 28);
    }

    return 0;
}