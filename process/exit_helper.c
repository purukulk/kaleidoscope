#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>

void signal_handler(int sig)
{
    if(sig == 2)
        exit(EXIT_SUCCESS);
    else
        exit(3);
}

int main()
{
    int i=10, p, s;
    signal(SIGINT, &signal_handler);
    printf("pid: %d\n", getpid());
    p = fork();
    if(p == 0)
    {
        printf("child pid: %d\n", getpid());
        while(i < 1000)
        {
            printf("abcd\n");
            i++;
            sleep(1);
        }
    }
    else if(p > 0)
        wait(&s);
    return 0;
}
