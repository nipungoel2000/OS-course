#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>

void helper(struct rlimit *r, int ret)
{
    if (ret == -1)
        printf("%d\n", errno);
    else
        printf("Soft limit:%lu    Hard limit:%lu\n", r->rlim_cur, r->rlim_max);
}

int main()
{
    struct rlimit rlim;
    int ret = getrlimit(RLIMIT_CORE, &rlim); //max size of core file
    helper(&rlim, ret);

    ret = getrlimit(RLIMIT_CPU, &rlim); //limit(in seconds) on the amount of CPU time that the process can consume
    helper(&rlim, ret);

    ret = getrlimit(RLIMIT_MSGQUEUE, &rlim); //limit on the number of bytes that can be allocated for POSIX msg queues.
    helper(&rlim, ret);

    ret = getrlimit(RLIMIT_STACK, &rlim); //max size of process stack, in bytes.
    helper(&rlim, ret);

    return 0;
}