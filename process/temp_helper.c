#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>

int main()
{
    printf("Parent: %d %ld\n", getpid(), syscall(SYS_gettid));
    int pid = fork();
    if(pid == 0)
    {
        printf("Child: %d %ld\n", getpid(), syscall(SYS_gettid));
        getchar();
    }
    getchar();
    return 0;
}
