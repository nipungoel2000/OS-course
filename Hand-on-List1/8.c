#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("file8.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("file open failed\n");
    };
    char *c;
    int i = 0;
    int n;
    char *buf;
    while (n = read(fd, c, 1))
    {
        if (n == -1)
            perror("error while reading\n");

        if (*c == '\n')
        {
            //printf("i = %d\n", i);
            buf = (char *)malloc(i * sizeof(char));
            //printf("%d %d\n",fd,t);
            if (i > 0)
                lseek(fd, -(i + 1), SEEK_CUR);
            read(fd, buf, i+1);
            printf("%s", buf);
            i = 0;
        }
        else
        {
            i++;
        }
    }
    //printf("i= %d\n", i);
    buf = (char *)malloc(i * sizeof(char));
    lseek(fd, -(i), SEEK_CUR);
    read(fd, buf, i);
    printf("%s\n", buf);
    int ret = close(fd);
    free(buf);
    printf("ret = %d\n", ret);
}