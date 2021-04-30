#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include<string.h>

int main()
{   
    struct timeval t;
    t.tv_sec = 10;
    t.tv_usec = 0;
    select(0, NULL, NULL, NULL, &t);
    char val[1024]={};
    scanf("%s",val);
    printf("%s\n",val);
    return 0;
}