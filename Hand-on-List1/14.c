#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/stat.h>
// https://linux.die.net/man/2/stat
// https://man7.org/linux/man-pages/man7/environ.7.html
int main(int argc, char * argv[])
{
    int a;
    for(a = 1; a < argc; a ++) {
        struct stat buf;
        stat(argv[a], &buf);
        // mode_t sMode=buf.st_mode;
        // printf("%d\n",S_ISLNK(buf.st_mode));
        printf("%d\n",S_ISREG(buf.st_mode));
        if(S_ISDIR(buf.st_mode)) {
            printf("%s\n","File is a directory");
        }
        // use lstat  for link, otherwise it will go to the pointed file.
        else if(S_ISLNK(buf.st_mode)) {
            printf("%s\n","File is a Symlink");
        }
        else if(S_ISREG(buf.st_mode)) {
            printf("%s\n","File is a Regular File");
        }
        
        else if(S_ISFIFO(buf.st_mode)) {
            printf("%s\n","File is a FIFO");
        }
        else if(S_ISBLK(buf.st_mode)) {
            printf("%s\n","File is a Block");
        }
        else {
            printf("%s\n","File is UNKNOWN");
        }
    }
    return 0;
 
}   