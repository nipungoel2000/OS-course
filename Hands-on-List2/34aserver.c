#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

struct sockaddr_in serv, cli;

int main(int argc, char *argv[])
{
    int portno = atoi(argv[1]);
    int opt = 1;
    //Creating socket file descriptor
    int sd = socket(AF_INET, SOCK_STREAM, 0); //sd is socket descriptor SOCK_STREAM-->TCP
    if (sd == 0)
    {
        perror("Socket Failed");
        exit(0);
    }

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(0);
    }
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(portno); //big endian(host to socket)

    //Attaching sockcet to ip and port
    int ret = bind(sd, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0)
    {
        perror("Bind failed");
        exit(0);
    }

    ret = listen(sd, 2); //sd,backlog
    if (ret < 0)
    {
        perror("Listen failure");
        exit(0);
    }

    printf("Connection Established Successfully\n");

    int flag = 1;
    while (flag)
    {
        unsigned int sz = sizeof(cli);
        int nsd = accept(sd, (struct sockaddr *)&cli, &sz); //blocking system call
        if (nsd < 0)
        {
            perror("Accept");
            exit(0);
        }
        if (!fork()) //in child process
        {
            close(sd);
            char buf[1024];
            read(nsd, buf, sizeof(buf));
            printf("Message From Client:  %s\n", buf);
            char buff[1024];
            printf("Enter your message: ");
            scanf("%s", buff);
            write(nsd, buff, sizeof(buff));
            printf("Sent from server\n");
            exit(0);
        }
        else
        {
            close(nsd);
        }
    }
    close(sd);
    return 0;
}