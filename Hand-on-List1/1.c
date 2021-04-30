#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h> 

int main()
{
	
	creat("source", O_CREAT | 0777);

	symlink("source", "symlnk");

	link("source","hardlink");

	mknod("myfif", S_IFIFO | 0777, 0);

	return 0;
}