#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rlim;

    int ret = getrlimit(RLIMIT_STACK, &rlim); //max size of process stack, in bytes.
    if (ret == -1)
    {
        printf("Error in retrieving resource limits\n");
        exit(0);
    }
    else
    {
        printf("Soft limit:%lu    Hard limit:%lu\n", rlim.rlim_cur, rlim.rlim_max);
        rlim.rlim_cur += 4;
        printf("Changing soft limit...\n");
        setrlimit(RLIMIT_STACK, &rlim);
        printf("Changed...\n");
        getrlimit(RLIMIT_STACK, &rlim);
        printf("Soft limit:%lu    Hard limit:%lu\n", rlim.rlim_cur, rlim.rlim_max);
    }
    return 0;
}