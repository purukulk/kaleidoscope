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
    getchar();
    return 0;
}

int main()
{
    int ret;
    pthread_t t1, t2;
    printf("Process's PID: %d\n", getpid());
    printf("Process's TID: %ld\n", syscall(SYS_gettid));
    sleep(1);
    pthread_create(&t1, NULL, func, NULL);
    pthread_setname_np(t1, "Thread 1");
    pthread_create(&t2, NULL, func, NULL);
    pthread_setname_np(t2, "Thread 2");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
