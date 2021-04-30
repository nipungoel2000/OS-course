#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    char buf[100];
    int fd = open("myfifo", O_RDONLY);
    read(fd, buf, sizeof(buf));
    printf("Message : %s\n", buf);
    close(fd);
    return 0;
}