#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int a=creat("source",O_CREAT);
    printf("%d\n",a);
	return 0;
}
