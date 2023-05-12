#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        printf("PID = %d\n", getpid());
        printf("PPID = %d\n", getppid());
        execl("/bin/sleep", "/bin/sleep", "100000", NULL);
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
