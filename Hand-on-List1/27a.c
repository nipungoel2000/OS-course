#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("Using execl\n");
    execl("/bin/ls", "ls", "-Rl", NULL);
    //printf("Done\n");
    return 0;
}