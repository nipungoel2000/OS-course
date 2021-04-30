#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler(int sig)
{
    printf("Received SIGSEGV signal: %d\n", sig);
    printf("Exiting....\n");
    exit(0);
}
// https://www-uxsup.csx.cam.ac.uk/courses/moved.Building/signals.pdf
/*SIGSEGV is caused
by an invalid memory reference or segmentation fault. */

int main()
{
    signal(SIGSEGV, my_sig_handler);
    printf("Catching SIGSEGV\n");
    int *p1 = NULL;
    int *p2 = malloc(sizeof(int));
    int k = *p1; //change to p2 for valid memory assignment
    printf("%d\n", k);
    printf("No SIGSEGV signal received\n");
    return 0;
}
