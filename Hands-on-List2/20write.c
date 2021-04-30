#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mkfifo("myfifo", S_IFIFO | 0777); //creating a fifo if does not exist
    char buf[100];
    int fd = open("myfifo", O_WRONLY);
    printf("Enter your message: \n");
    scanf(" %[^\n]", buf);
    write(fd, buf, sizeof(buf));
    close(fd);
    return 0;
}