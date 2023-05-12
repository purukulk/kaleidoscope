#include<errno.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int i = 10;
    printf("pid: %d\n", getpid());

    while (i++ < 1000)
    {
        printf("abcd\n");
        sleep(1);
    }

    return 0;
}