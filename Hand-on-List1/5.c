#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int fd1=creat("file1",O_CREAT);
    int fd2=creat("file2",O_CREAT);
    int fd3=creat("file3",O_CREAT);
    int fd4=creat("file4",O_CREAT);
    int fd5=creat("file5",O_CREAT);
    // printf("%d %d %d %d %d\n",fd1,fd2,fd3,fd4,fd5);
    while(1)
	{
                 
	}    
    return 0;
}
