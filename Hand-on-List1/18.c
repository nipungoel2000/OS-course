#include <stdio.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct record
{
    int num;
    char *name;
} rec;

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY);

    rec *myrec1 = (rec *)malloc(sizeof(myrec1));
    rec *myrec2 = (rec *)malloc(sizeof(myrec2));
    rec *myrec3 = (rec *)malloc(sizeof(myrec3));

    myrec1->name = "stud1";
    myrec1->num = 1;
    myrec2->name = "stud2";
    myrec2->num = 2;
    myrec3->name = "stud3";
    myrec3->num = 3;

    printf("Writing record1 : %d %s\n", myrec1->num, myrec1->name);
    lseek(fd, 0, SEEK_END);
    write(fd, myrec1, sizeof(rec));

    printf("Writing record2 : %d %s\n", myrec2->num, myrec2->name);
    lseek(fd, 0, SEEK_END);
    write(fd, myrec2, sizeof(rec));

    printf("Writing record3 : %d %s\n", myrec3->num, myrec3->name);
    lseek(fd, 0, SEEK_END);
    write(fd, myrec3, sizeof(rec));

    return 0;
}