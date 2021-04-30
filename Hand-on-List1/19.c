#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    clock_t start, end;
    start = clock();
    int res = getpid();
    end = clock();
    printf("Start time : %ld %ld %d\n", start, end, res);
    printf("Time taken(using time stamp counter) : %ld\n", (end - start));
    //printf("%ld\n", CLOCKS_PER_SEC);
}