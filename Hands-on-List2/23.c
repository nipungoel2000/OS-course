#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    long PIPE_BUF, OPEN_MAX;

    PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
    OPEN_MAX = sysconf(_SC_OPEN_MAX);
    printf("Max number of files that can be opened within a process: %ld\n", OPEN_MAX);
    printf("Size of a pipe(circular buffer): %ld\n", PIPE_BUF);
    return 0;
}