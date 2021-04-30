#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("Using execvp\n");
    char *args[] = {"ls", "-Rl", NULL};
    execvp("/bin/ls", args);
    //printf("Done\n");
    return 0;
}