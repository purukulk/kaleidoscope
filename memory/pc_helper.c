#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int s;
    int pid = fork();
    if(pid == 0)
    {
        //getchar();
        //while(1);
        //printf("exec executing now!\n");
        execl("/bin/sleep", "/bin/sleep", "100000", NULL);
    }
    printf("PID = %d\n", getpid());
    wait(&s);
    getchar();

    return 0;
}
