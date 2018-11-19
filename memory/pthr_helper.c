#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void *func(void *data)
{
    printf("Pthreads's PID: %d\n", getpid());
    printf("Pthreads's TID: %ld\n", syscall(SYS_gettid));
    return 0;
}

int main()
{
    int ret;
    pthread_t t1;
    printf("Process's PID: %d\n", getpid());
    printf("Process's TID: %ld\n", syscall(SYS_gettid));
    sleep(1);
    ret = pthread_create(&t1, NULL, func, NULL);
    pthread_join(t1, NULL);
    return 0;
}
