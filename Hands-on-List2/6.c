#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int cnt = 0;

void threadInfo()
{
    printf("Thread number: %lu\t counter value: %d\n", pthread_self(), ++cnt);
}

int main(void)
{

    pthread_t mythread;

    for (int i = 0; i < 3; i++)
    {

        pthread_create(&mythread, NULL, (void *)threadInfo, NULL);
    }

    pthread_exit(NULL);
}