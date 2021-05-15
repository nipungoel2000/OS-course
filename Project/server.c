#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
// #include "options.h"
#include "helper.c"

void *clientHandler(void *);

int main()
{
    int portno = PORT;
    int opt = 1;
    struct sockaddr_in serv, cli;
    int sd;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket Failed");
        exit(1);
    }

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(1);
    }
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(portno); //big endian(host to socket)

    //Attaching sockcet to ip and port
    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }

    if (listen(sd, 2) < 0)
    {
        perror("Listen failure");
        exit(1);
    }

    printf("Server : Ready To Listen\n");

    while (1)
    {
        unsigned int sz = sizeof(cli);
        int nsd = accept(sd, (struct sockaddr *)&cli, &sz);
        if (nsd < 0)
        {
            perror("Accept failure");
            exit(1);
        }
        pthread_t tid;
        if (pthread_create(&tid, NULL, clientHandler, (void *)&nsd) < 0)
        {
            perror("Thread Failure");
            exit(1);
        }
        printf("Handler assigned to Client\n");
    }
    return 0;
}

void *clientHandler(void *args)
{
    int nsd = *(int *)args;
    printf("sock : %d\n", nsd);
    int flag = 1, option;
    char username[128], password[128];
    while (flag)
    {
        char opt_str[16];
        char ret_msg[1024];
        int n = read(nsd, opt_str, sizeof(opt_str));
        if (n <= 0)
            break;
        option = atoi(opt_str);

        if (option == SIGN_UP_AS_ADMIN || option == SIGN_UP_AS_JOINT || option == SIGN_UP_AS_USER)
        {
            // printf("Here\n");
            read(nsd, username, sizeof(username));
            read(nsd, password, sizeof(password));
            // printf("%s\n %s\n", username, password);
            int ret = validate_signup(option, username, password, 0);
            if (ret == -1)
                strcpy(ret_msg, "SIGN UP FAILED: Username already exists");
            else
                strcpy(ret_msg, "SIGN UP SUCCESSFULL");
        }

        else if (option == SIGN_IN_AS_ADMIN || option == SIGN_IN_AS_JOINT || option == SIGN_IN_AS_USER)
        {
            read(nsd, username, sizeof(username));
            read(nsd, password, sizeof(password));
            // printf("%s\n %s\n", username, password);
            int ret = validate_signin(option, username, password);
            if (ret == -1)
                strcpy(ret_msg, "SIGN IN FAILED: Incorrect Username or Password");
            else
                strcpy(ret_msg, "SIGN IN SUCCESSFULL");
        }
        else if (option == DEPOSIT)
        {
            char amtstr[16];
            read(nsd, amtstr, sizeof(amtstr));
            int amt = atoi(amtstr);
            int ret = deposit(username, amt);
            if (ret == -1)
                strcpy(ret_msg, "Deposit Failed");
            else
                strcpy(ret_msg, "Amount Deposited Successfully");
        }
        else if (option == WITHDRAW)
        {
            char amtstr[16];
            read(nsd, amtstr, sizeof(amtstr));
            int amt = atoi(amtstr);
            int ret = withdraw(username, amt);
            if (ret == -1)
                strcpy(ret_msg, "Withdraw Failed");
            else
                strcpy(ret_msg, "Withdraw Successfull");
        }
        else if (option == BALANCE_CHECK)
        {
            int bal = getBalance(username);
            if (bal == -1)
                strcpy(ret_msg, "Failed");
            else
            {
                strcpy(ret_msg, "Balance in you account : ");
                char balstr[16];
                sprintf(balstr, "%d", bal);
                strcat(ret_msg, balstr);
            }
        }
        else if (option == PWD_CHANGE)
        {
            char npwd[128];
            read(nsd, npwd, sizeof(npwd));
            int ret = changePwd(username, npwd);
            if (ret == -1)
                strcpy(ret_msg, "Password Change Failed");
            else
                strcpy(ret_msg, "Password Change Successfull");
        }
        else if (option == VIEW_DETAILS)
        {
            strcpy(ret_msg, getDetails(username));
        }
        else if (option == ADD_USER)
        {
            char typestr[32], uname[128], pwd[128];
            read(nsd, typestr, sizeof(typestr));
            read(nsd, uname, sizeof(uname));
            read(nsd, pwd, sizeof(pwd));
            int type = atoi(typestr);
            int ret = validate_signup(type, uname, pwd, 0);
            if (ret == -1)
                strcpy(ret_msg, "Add User failed.");
            else
                strcpy(ret_msg, "Add User Successfull");
        }
        else if (option == MOD_USER)
        {
            char uname[128], newuname[128], newpwd[128];
            read(nsd, uname, sizeof(uname));
            read(nsd, newuname, sizeof(newuname));
            read(nsd, newpwd, sizeof(newpwd));
            int ret = modUser(uname, newuname, newpwd);
            if (ret == -1)
                strcpy(ret_msg, "Failed");
            else
                strcpy(ret_msg, "Success");
        }
        else if (option == DEL_USER)
        {
            char uname[128];
            read(nsd, uname, sizeof(uname));
            int ret = delUser(uname);
            if (ret != 0)
                strcpy(ret_msg, "Delete failed.");
            else
                strcpy(ret_msg, "Delete Successful.");
        }
        else if (option == GET_USER_DETAILS)
        {
            char uname[128];
            read(nsd, uname, sizeof(uname));
            strcpy(ret_msg, getDetails(uname));
        }
        else if (option == EXIT)
        {
            flag = 0;
        }
        write(nsd, ret_msg, sizeof(ret_msg));
        // printf("flag = %d\n oprion = %d\n", flag, option);
        // flag = 0;
    }
    close(nsd);
}
