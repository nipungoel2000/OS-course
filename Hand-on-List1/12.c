#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int fd1=open("test.txt",O_RDONLY);
    // printf("%d %d %d %d %d\n",fd1,fd2,fd3,fd4,fd5);
    int c=O_ACCMODE & fcntl(fd1,F_GETFL);
    if(c==O_RDWR)
        printf("%s\n","read write");
    else if(c==O_RDONLY)
        printf("%s\n","read only");
    else
        printf("%s\n","write only");
        

    return 0;
}