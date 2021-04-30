#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include<string.h>
int main()
{
    int fd1=open("test.txt",O_RDONLY);
    
    struct stat fileStat;
    if(fstat(fd1, &fileStat)<0) return 1;
    printf("File inode: %lu\n",fileStat.st_ino);
    printf("Number of Hard Links: %lu\n",fileStat.st_nlink);
    printf("File uid: %u\n",fileStat.st_uid);
    printf("File gid: %u\n",fileStat.st_gid);
    printf("File size: %lu\n",fileStat.st_size);
    printf("Block size: %lu\n",fileStat.st_blksize);
    printf("Number of Blocks: %lu\n",fileStat.st_blocks);
    printf("Time of last access: %lu\n",fileStat.st_atime);
    printf("Time of last modification: %lu\n",fileStat.st_mtime);
    printf("Time of last change: %lu\n",fileStat.st_ctime);
  
    return 0;
}
