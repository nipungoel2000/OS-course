#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int a=open("test.txt",O_RDWR);
    int b=open("test.txt",O_EXCL);
    // char *x=(char*)malloc(10*sizeof(char));
    // int c=read(b,x,10);
    // printf("%s\n",x);

	return 0;          
}