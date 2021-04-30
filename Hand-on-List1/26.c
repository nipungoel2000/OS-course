#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *args[] = {"./26exec", "Hello from 26.c", NULL};
    execvp(args[0], args);
    /*All statements are ignored after execvp() call as this whole  
        process(26.c) is replaced by another process (26exec.c) */
    printf("Now in 26.c again...Ending..\n");
    return 0;
}