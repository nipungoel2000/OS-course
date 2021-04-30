#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("Using execv\n");
    char *args[] = {"ls", "-Rl", NULL};
    execv("/bin/ls", args);
    //printf("Done\n");
    return 0;
}