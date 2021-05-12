#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

struct sockaddr_in serv;

int main(int argc, char *argv[])
{
    int portno = atoi(argv[1]);

    int sd = socket(AF_INET, SOCK_STREAM, 0); //sd is socket descriptor
    if (sd == 0)
    {
        perror("Socket Failure");
        exit(0);
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(portno);

    if (connect(sd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        printf("Connection failed\n");
        return -1;
    }

    printf("Connection Established Successfully\n");
    char buf[1024], buff[1024];
    printf("Enter your message: ");
    scanf("%s", buff);
    write(sd, buff, sizeof(buff));
    printf("Data sent to server\n");
    read(sd, buf, 1024);
    printf("Data from server: %s\n", buf);

    getchar();
    printf("Press enter to exit\n");
    getchar();
    close(sd);
    return 0;
}