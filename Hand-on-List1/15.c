#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    extern char **environ;//
    int i=0;
    while(environ[i])
    {
        printf("%s\n",environ[i]);
        i++;   
    }
    // for(int i=0;i<sizeof(environ)/sizeof(char*);i++)
    //    printf("%s\n",environ[i]);
}   