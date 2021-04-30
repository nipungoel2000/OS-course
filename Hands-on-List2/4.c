#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

unsigned long long rdtsc()
{
    unsigned long long dst;
    __asm__ __volatile__("rdtsc"
                         : "=A"(dst));

    return dst;
}
int main()
{
    long long int start, end;
    start = rdtsc();
    for (int i = 1; i <= 100; i++)
    {
        getppid();
    }
    end = rdtsc();
    printf("Time taken to execute 100 getppid() system calls : %llu\n", end - start);
    return 0;
}
/*System can provide very high resolution time measurements through the time-stamp counter which counts the number of instructions since boot. 
To measure Time Stamp Counter (TSC)*/
//CPU cycles