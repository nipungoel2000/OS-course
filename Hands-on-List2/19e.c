#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int status = mkfifo("myfifo2", S_IFIFO | 0744);
    if (status == -1)
    {
        printf("FIFO creation falied\n");
        exit(0);
    }
    printf("Success\n");
    return 0;
}