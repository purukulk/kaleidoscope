#define _GNU_SOURCE
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid, i;
    printf("Process's PID: %d\n", getpid());
    for(i=0;i<5;i++)
    {
        pid = fork();
        if(pid == 0)
        {
            printf("Child's PID: %d\n", getpid());
            getchar();       
        }
    }
    getchar();
    return 0;
}
