#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sched.h>

int main()
{
    int pid = getpid();

    int policy = sched_getscheduler(pid);
    printf("Current sheduling policy for this process : %d\n", policy);

    struct sched_param schdp;
    int p = 50;
    schdp.sched_priority = p;

    sched_setscheduler(pid, SCHED_FIFO, &schdp);
    int newp = sched_getscheduler(pid);
    printf("Current sheduling policy for this process : %d\n", newp);
    return 0;
}

//Run with sudo ./a.out
// RR - 2
// FIFO - 1
//OTHER - 0