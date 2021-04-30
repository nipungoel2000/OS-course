#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("file11.txt", O_RDWR | O_APPEND);

    if (fd < 0)
        perror("Error opening the file\n");

    int desc_cp1 = dup(fd);
    write(fd, "Hello World\n", 12);
    write(desc_cp1, "Using dup\n", 10);

    int desc_cp2;

    dup2(fd,desc_cp2);
    write(desc_cp2, "Using dup2\n", 11);
    // dup2(fd, 1);
    // printf("Using dup2 and stdout\n");

    int desc_cp3=fcntl(fd,F_DUPFD);
    write(desc_cp3, "Using fcntl\n", 12);


}