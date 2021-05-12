#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void thread_func()
{
    printf("Thread id is %ld\n", pthread_self());
}
int main()
{
    pthread_t mythread;
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&mythread, NULL, (void *)thread_func, NULL);
    }
    pthread_exit(NULL);
    return 0;
}
// gcc 7.c -lpthread
/*This program, when compiled, requires linkage to the
POSIX thread library, which can be linked by specifying the
pthread library to the gcc compiler.*/