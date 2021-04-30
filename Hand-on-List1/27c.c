#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

int main()
{
    printf("Using execle\n");
    execle("/bin/ls", "ls", "-Rl", NULL, environ);
    //printf("Done\n");
    return 0;
}