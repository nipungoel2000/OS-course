#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

int main()
{
    mkfifo("myfifo", S_IFIFO | 0777); //creating a fifo if does not exist

    char buf[100];
    int fd = open("myfifo", O_RDWR);
    printf("Enter your message: \n");
    fflush(stdout);

    fd_set rfds;
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    FD_ZERO(&rfds);   //Clearing all file descriptors
    FD_SET(0, &rfds); //Adding stdin in file descriptor
    int retval = select(1, &rfds, NULL, NULL, &tv);
    if (retval == -1)
        perror("select()");
    else if (!retval)
        printf("No data within ten seconds.\n");
    else //Data available
    {
        char buf2[100];
        fgets(buf, sizeof(buf2), stdin);
        write(fd, buf, sizeof(buf2));
        printf("Reading from fifo.....%s\n", buf2);
        sleep(3);
        read(fd, buf2, sizeof(buf2));
        printf("%s\n", buf2);
    }
    close(fd);
    return 0;
}