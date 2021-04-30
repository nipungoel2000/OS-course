#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

struct sockaddr_in serv, cli;

int main()
{
    int sd = socket(AF_UNIX, SOCK_STREAM,0); //sd is socket descriptor
    serv.sin_family = AF_INET;

}