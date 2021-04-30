#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mkfifo("myfifo2", S_IFIFO | 0777); //creating a fifo if does not exist

    char buf1[100];
    int fd1 = open("myfifo1", O_RDONLY);
    read(fd1, buf1, sizeof(buf1));
    printf("Message : %s\n", buf1);
    close(fd1);

    int fd2 = open("myfifo2", O_WRONLY);
    char buf2[100];
    printf("Enter your message: \n");
    scanf(" %[^\n]", buf2);
    write(fd2, buf2, sizeof(buf2));
    close(fd2);
    return 0;
}