#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        printf("Child pid: %d\n", getpid());
        while(1);
    }
    else
    {
        printf("Parent pid: %d\n", getpid());
    }
    
    getchar();
    return 0;
}
