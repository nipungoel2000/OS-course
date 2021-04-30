#include <stdio.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct record
{
    int num;
    char *name;
} rec;

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1)
    {
        printf("Unable to open the file\n");
        exit(1);
    }

    printf("Enter the record number you wish to lock(from 1 to 3)\n");
    int num;
    scanf("%d", &num);
    getchar(); //for clearing buffer
    struct flock flk;
    //memset(&flk, 0, sizeof(flk));

    flk.l_type = F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start = sizeof(rec) * (num - 1);
    flk.l_len = sizeof(rec);
    flk.l_pid = getpid();

    printf("Before locking...\n");

    int ret = fcntl(fd, F_SETLKW, &flk);

    if (ret == -1)
    {
        printf("Attempt to write lock failed\n");
        exit(1);
    }
    else
    {
        printf("Write locked with lock type %d : ... hit Enter to unlock\n", flk.l_type);
        getchar();
        flk.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &flk);
    }
    printf("Unlocked\n");
    // printf("Lock type : %d\n", flk.l_type);
    return 0;
}