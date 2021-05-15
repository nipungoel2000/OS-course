#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include "options.h"

void handle(int);
int printOptions(int);
int getDetails(int, int);
void userHandle(int);
void adminHandle(int);

int main()
{
    struct sockaddr_in serv;
    int sd;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket Failure");
        exit(1);
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        exit(1);
    }

    if (connect(sd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("Connection failed");
        exit(1);
    }

    printf("Client : Connection to Bank Server Established Successfully\n");
    handle(sd);
    return 0;
}

void handle(int sd)
{
    printf("Sock : %d\n", sd);
    int option = printOptions(START);
    int ret;
    if (option == INVALID)
    {
        printf("Invalid Option\n");
        exit(1);
    }
    ret = getDetails(sd, option);
    while (1)
    {
        if (ret == SIGN_IN_AS_USER || ret == SIGN_UP_AS_USER || ret == SIGN_IN_AS_JOINT || ret == SIGN_UP_AS_JOINT)
        {
            userHandle(sd);
        }
        else if (ret == SIGN_IN_AS_ADMIN || ret == SIGN_UP_AS_ADMIN)
        {
            adminHandle(sd);
        }
        else
        {
            exit(1);
        }
    }
}
void userHandle(int sd)
{
    int opt = printOptions(USER);
    if (opt == INVALID)
    {
        printf("Invalid Option\n");
        exit(1);
    }
    char opt_str[16], ret_msg[1024];
    sprintf(opt_str, "%d", opt);
    write(sd, opt_str, sizeof(opt_str));

    if (opt == DEPOSIT)
    {
        char amt[16];
        printf("Enter amount to be deposited: ");
        scanf("%s", amt);
        write(sd, amt, sizeof(amt));
    }
    else if (opt == WITHDRAW)
    {
        char amt[16];
        printf("Enter amount to be withdrawn: ");
        scanf("%s", amt);
        write(sd, amt, sizeof(amt));
    }
    else if (opt == BALANCE_CHECK)
    {
        ;
    }
    else if (opt == PWD_CHANGE)
    {
        char newpwd[128];
        printf("Enter your new password: ");
        scanf("%s", newpwd);
        write(sd, newpwd, sizeof(newpwd));
    }
    else if (opt == VIEW_DETAILS)
    {
        ;
    }
    else if (opt == EXIT)
    {
        exit(0);
    }
    read(sd, ret_msg, sizeof(ret_msg));
    printf("%s\n", ret_msg);
}
void adminHandle(int sd)
{
    int opt = printOptions(ADMIN);
    if (opt == INVALID)
    {
        printf("Invalid Option\n");
        exit(1);
    }
    char opt_str[16], ret_msg[1024];
    sprintf(opt_str, "%d", opt);
    write(sd, opt_str, sizeof(opt_str));

    if (opt == ADD_USER)
    {
        int type;
        char typestr[32], uname[128], pwd[128];
        printf("Enter type of user(1 or 2) :\n1. Normal \n2. Joint\n");
        scanf("%d", &type);
        if (type == 1)
            type = SIGN_UP_AS_USER;
        else if (type == 2)
            type = SIGN_UP_AS_JOINT;
        else
        {
            perror("Invalid Input");
            exit(1);
        }
        sprintf(typestr, "%d", type);
        printf("Enter username : ");
        scanf("%s", uname);
        printf("Enter Password : ");
        scanf("%s", pwd);
        write(sd, typestr, sizeof(typestr));
        write(sd, uname, sizeof(uname));
        write(sd, pwd, sizeof(pwd));
    }
    else if (opt == MOD_USER)
    {
        char uname[128], newuname[128], newpwd[128];
        printf("Enter old username : ");
        scanf("%s", uname);
        printf("Enter new username : ");
        scanf("%s", newuname);
        printf("Enter new password : ");
        scanf("%s", newpwd);

        write(sd, uname, sizeof(uname));
        write(sd, newuname, sizeof(newuname));
        write(sd, newpwd, sizeof(newpwd));
    }
    else if (opt == DEL_USER)
    {
        char uname[128];
        printf("Enter username : ");
        scanf("%s", uname);
        write(sd, uname, sizeof(uname));
    }
    else if (opt == GET_USER_DETAILS)
    {
        char uname[128];
        printf("Enter username : ");
        scanf("%s", uname);
        write(sd, uname, sizeof(uname));
    }
    else if (opt == EXIT)
    {
        exit(0);
    }
    read(sd, ret_msg, sizeof(ret_msg));
    printf("%s\n", ret_msg);
}
int getDetails(int sd, int option)
{
    char uname[128];
    char pwd[128];
    char opt_str[16];
    char ret_msg[1024];
    int opt = printOptions(option);
    if (opt == INVALID)
    {
        printf("Invalid Option\n");
        exit(1);
    }
    printf("Enter Username : ");
    scanf("%s", uname);
    printf("Enter password : ");
    scanf("%s", pwd);

    sprintf(opt_str, "%d", opt);
    printf("(Sending.. %s %s %s)\n", opt_str, uname, pwd);
    write(sd, opt_str, sizeof(opt_str));
    write(sd, uname, sizeof(uname));
    write(sd, pwd, sizeof(pwd));
    read(sd, ret_msg, sizeof(ret_msg));
    printf("%s\n", ret_msg);
    if (strcmp(ret_msg, "SIGN UP SUCCESSFULL") != 0 && strcmp(ret_msg, "SIGN IN SUCCESSFULL") != 0)
        exit(1);
    return opt;
}
int printOptions(int type)
{
    int option;
    if (type == START)
    {
        printf("\n\nChoose any of the following options:\n");
        printf("1. SIGN UP\n");
        printf("2. SIGN IN\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            return SIGNUP;
        case 2:
            return SIGNIN;
        default:
            return INVALID;
        }
    }
    else if (type == SIGNUP)
    {
        printf("\n\nChoose any of the following options:\n");
        printf("1. SIGN UP As Normal User\n");
        printf("2. SIGN UP As Join Account User\n");
        printf("3. SIGN UP As Administrator\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            return SIGN_UP_AS_USER;
        case 2:
            return SIGN_UP_AS_JOINT;
        case 3:
            return SIGN_UP_AS_ADMIN;
        default:
            return INVALID;
        }
    }
    else if (type == SIGNIN)
    {
        printf("\n\nChoose any of the following options:\n");
        printf("1. SIGN IN As Normal User\n");
        printf("2. SIGN IN As Join Account User\n");
        printf("3. SIGN IN As Administrator\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            return SIGN_IN_AS_USER;
        case 2:
            return SIGN_IN_AS_JOINT;
        case 3:
            return SIGN_IN_AS_ADMIN;
        default:
            return INVALID;
        }
    }
    else if (type == USER)
    {
        printf("\n\nWhat do you want to do?\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Balance Enquiry\n");
        printf("4. Change Password\n");
        printf("5. View User details\n");
        printf("6. Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            return DEPOSIT;
        case 2:
            return WITHDRAW;
        case 3:
            return BALANCE_CHECK;
        case 4:
            return PWD_CHANGE;
        case 5:
            return VIEW_DETAILS;
        case 6:
            return EXIT;
        default:
            return INVALID;
        }
    }
    else if (type == ADMIN)
    {
        printf("\n \nWhat do you want to do?\n");
        printf("1. Add User\n");
        printf("2. Modify User\n");
        printf("3. Delete User\n");
        printf("4. Get User Account Details\n");
        printf("5. Exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            return ADD_USER;
        case 2:
            return MOD_USER;
        case 3:
            return DEL_USER;
        case 4:
            return GET_USER_DETAILS;
        case 5:
            return EXIT;
        default:
            return INVALID;
        }
    }
}