#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void *func2(void *data)
{
    printf("Pthreads's PID: %d\n", getpid());
    printf("Pthreads's TID: %ld\n", syscall(SYS_gettid));
    getchar();
    return 0;
}
void *func(void *data)
{
    int pid;
    pthread_t t2;
    printf("Pthreads's PID: %d\n", getpid());
    printf("Pthreads's TID: %ld\n", syscall(SYS_gettid));
//    pid = fork();
//    if(pid == 0)
//    {
//        printf("Pthreads's child's PID: %d\n", getpid());
//        printf("Pthreads's child's TID: %ld\n", syscall(SYS_gettid));
//        getchar();
//    }
//    else if(pid > 0)
//        getchar();
    getchar();
//    sleep(1);
//    pthread_create(&t2, NULL, func2, NULL);
//    pthread_join(t2, NULL);
    return 0;
}

int main()
{
    int ret;
    pthread_t t1;
    printf("Process's PID: %d\n", getpid());
    printf("Process's TID: %ld\n", syscall(SYS_gettid));
    sleep(1);
    pthread_create(&t1, NULL, func, NULL);
    pthread_setname_np(t1, "Thread 1");
    pthread_join(t1, NULL);
    return 0;
}
