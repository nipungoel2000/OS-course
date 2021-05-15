#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include "options.h"

int validate_signup(int, char *, char *, int);
int validate_signin(int, char *, char *);
int deposit(char *, int);
int withdraw(char *, int);
int getBalance(char *);
int changePwd(char *, char *);
char *getDetails(char *);
int delUser(char *);
int modUser(char *, char *, char *);

int deposit(char *uname, int amt)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(struct user);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    int fd = open(fname, O_RDWR);
    // printf("fname : %s\n", fname);
    if (fd == -1) //doen not exist
    {
        perror("File open failed");
        return -1;
    }

    fcntl(fd, F_SETLKW, &lock);
    //start of critical section
    lseek(fd, sizeof(struct user), SEEK_SET);
    struct account acc;
    read(fd, &acc, sizeof(struct account));
    acc.balance += amt;
    lseek(fd, sizeof(struct user), SEEK_SET);
    write(fd, &acc, sizeof(struct account));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    // end of critical section
    close(fd);
    return 0;
}
int withdraw(char *uname, int amt)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(struct user);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    int fd = open(fname, O_RDWR);
    // printf("fname : %s\n", fname);
    if (fd == -1) //doen not exist
    {
        perror("File open failed");
        return -1;
    }

    fcntl(fd, F_SETLKW, &lock);
    int check = 0;
    //start of critical section
    lseek(fd, sizeof(struct user), SEEK_SET);
    struct account acc;
    read(fd, &acc, sizeof(struct account));
    if (acc.balance < amt)
        check = 1;
    else
    {
        acc.balance -= amt;
        lseek(fd, sizeof(struct user), SEEK_SET);
        write(fd, &acc, sizeof(struct account));
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    // end of critical section
    close(fd);
    if (check)
        return -1;
    return 0;
}
int getBalance(char *uname)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizeof(struct user);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    int fd = open(fname, O_RDWR);
    // printf("fname : %s\n", fname);
    if (fd == -1) //doen not exist
    {
        perror("File open failed");
        return -1;
    }

    fcntl(fd, F_SETLKW, &lock);
    //start of critical section
    lseek(fd, sizeof(struct user), SEEK_SET);
    struct account acc;
    read(fd, &acc, sizeof(struct account));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    // end of critical section
    close(fd);
    return acc.balance;
}
int delUser(char *uname)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");
    return remove(fname);
}
int modUser(char *uname, char *newuname, char *newpwd)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int fd = open(fname, O_RDWR);
    // printf("fname : %s\n", fname);
    if (fd == -1) //doen not exist
    {
        perror("File open failed");
        return -1;
    }
    struct user u;
    struct account acc;
    fcntl(fd, F_SETLKW, &lock);
    //start of critical section
    read(fd, &u, sizeof(struct user));
    read(fd, &acc, sizeof(struct account));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    // end of critical section
    close(fd);

    int type;
    if (strcmp(u.type, "Normal") == 0)
        type = SIGN_UP_AS_USER;
    else if (strcmp(u.type, "Joint") == 0)
        type = SIGN_UP_AS_JOINT;
    else
        return -1;
    int ret = remove(fname);
    if (ret != 0)
        return -1;
    return validate_signup(type, newuname, newpwd, acc.balance);
}
int changePwd(char *uname, char *pwd)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct user);
    lock.l_pid = getpid();

    int fd = open(fname, O_RDWR);
    // printf("fname : %s\n", fname);
    if (fd == -1) //doen not exist
    {
        perror("File open failed");
        return -1;
    }

    fcntl(fd, F_SETLKW, &lock);
    //start of critical section
    lseek(fd, 0, SEEK_SET);
    struct user u;
    read(fd, &u, sizeof(struct user));
    strcpy(u.password, pwd);
    lseek(fd, 0, SEEK_SET);
    write(fd, &u, sizeof(struct user));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    // end of critical section
    close(fd);
    return 0;
}
char *getDetails(char *uname)
{
    char *buf = (char *)malloc(1024);
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int fd = open(fname, O_RDONLY);
    // printf("fname : %s\n", fname);
    if (fd == -1) //doen not exist
    {
        perror("File open failed");
        return "Error";
    }

    fcntl(fd, F_SETLKW, &lock);
    //start of critical section
    lseek(fd, 0, SEEK_SET);
    struct account acc;
    struct user u;
    read(fd, &u, sizeof(struct user));
    read(fd, &acc, sizeof(struct account));
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    // end of critical section
    close(fd);
    sprintf(buf, "Username: %s\nPassword: %s\ntype: %s\nBalance: %d\n", u.username, u.password, u.type, acc.balance);
    return buf;
}
int validate_signup(int opt, char *uname, char *pwd, int amt)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    int fd = open(fname, O_WRONLY);
    if (fd != -1) //already exists
        return -1;
    else
        close(fd);
    fd = open(fname, O_WRONLY | O_CREAT, 0744);
    if (fd == -1)
    {
        perror("Sign up error");
        return -1;
    }
    struct user usr;
    struct account acc;
    if (opt == SIGN_UP_AS_USER)
        strcpy(usr.type, "Normal");
    else if (opt == SIGN_UP_AS_JOINT)
        strcpy(usr.type, "Joint");
    else if (opt == SIGN_UP_AS_ADMIN)
        strcpy(usr.type, "Admin");
    strcpy(usr.username, uname);
    strcpy(usr.password, pwd);
    acc.balance = amt;
    write(fd, &usr, sizeof(struct user));
    write(fd, &acc, sizeof(struct account));
    close(fd);
    return 0;
}
int validate_signin(int opt, char *uname, char *pwd)
{
    char fname[256];
    strcpy(fname, uname);
    strcat(fname, ".txt");

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; //lock everything
    lock.l_pid = getpid();

    int fd = open(fname, O_RDONLY);
    // printf("fname : %s\n", fname);
    if (fd == -1) //doen not exist
    {
        perror("Sign in failed");
        return -1;
    }

    fcntl(fd, F_SETLKW, &lock);
    // start of critical section
    struct user u;
    lseek(fd, 0, SEEK_SET);
    read(fd, &u, sizeof(struct user));
    if ((strcmp(u.password, pwd) != 0) || (opt == SIGN_IN_AS_ADMIN && strcmp(u.type, "Admin") != 0) || (opt == SIGN_IN_AS_JOINT && strcmp(u.type, "Joint") != 0) || (opt == SIGN_IN_AS_USER && strcmp(u.type, "Normal") != 0))
        return -1;
    //end critical section
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    close(fd);
    return 0;
}