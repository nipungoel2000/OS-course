#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
   int f1, f2;
   char buff[50];
   long int n;
   f1 = open(argv[1], O_RDONLY);
   f2=open(argv[2], O_CREAT | O_WRONLY, 0700);
    while((n=read(f1, buff, 50))>0)
    {
        write(f2, buff, n);
    }
    close(f2);
 }