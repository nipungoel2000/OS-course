#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mkfifo("myfifo1", S_IFIFO | 0777); //creating a fifo if does not exist

    char buf1[100];
    int fd1 = open("myfifo1", O_WRONLY);
    printf("Enter your message: \n");
    scanf(" %[^\n]", buf1);
    write(fd1, buf1, sizeof(buf1));
    close(fd1);

    int fd2 = open("myfifo2", O_RDONLY);
    char buf2[100];
    read(fd2, buf2, sizeof(buf2));
    printf("Message : %s\n", buf2);
    close(fd2);
    return 0;
}