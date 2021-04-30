#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sched.h>

int main()
{
    int min_prior = sched_get_priority_min(SCHED_FIFO);
    int max_prior = sched_get_priority_max(SCHED_FIFO);
    printf("Minimum priority of real time: %d\n", min_prior);
    printf("Maximum priority of real time: %d\n", max_prior);
    return 0;
}