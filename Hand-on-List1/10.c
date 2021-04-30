#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int f1, f2;
    char buff[10]={"hello12345"};
    long int n;
    f1 = open(argv[1], O_RDWR);
    write(f1, buff, 10);
    int result=lseek(f1,10,SEEK_CUR);
    write(f1, buff, 10);
    printf("%d",result);
    // od -c test.txt
    return 0;
}