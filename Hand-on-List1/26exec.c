#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("This is the support file with input from 26.c - %s\n", argv[1]);
    return 0;
}
//Run using gcc 26exec.c -o 26exec
// ./26exec hello