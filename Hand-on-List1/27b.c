#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("Using execlp\n");
    execlp("/bin/ls", "ls", "-Rl", NULL);
    //printf("Done\n");
    return 0;
}