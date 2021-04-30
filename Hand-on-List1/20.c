#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
    int pid = getpid();
    int priority = getpriority(PRIO_PROCESS, pid);
    printf("Priority of current process: %d\n", priority);
    //Note lower the value higher the priority.
    int ret = nice(15);
    int priority_changed = getpriority(PRIO_PROCESS, pid);
    printf("Return value of nice : %d\n", ret);
    printf("Priority of current process(after changing using nice): %d\n", priority_changed);
}