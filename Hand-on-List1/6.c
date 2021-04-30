#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char msg[100]={};
    read(STDIN_FILENO,msg,100);
    write(STDOUT_FILENO,msg,100);
    return 0;
}