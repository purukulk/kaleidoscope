#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sigusr1_handler(int sig)
{
    fprintf(stderr, "SIGUSR1 handler invoked!\n");
    return;
}
void sigusr2_handler(int sig)
{
    fprintf(stderr, "SIGUSR2 handler invoked!\n");
    return;
}

int main()
{
    if(signal(SIGUSR1, &sigusr1_handler) == SIG_ERR)
        fprintf(stderr, "signal() error: %d: %s\n", errno, strerror(errno));

    if(signal(SIGUSR2, &sigusr2_handler) == SIG_ERR)
        fprintf(stderr, "signal() error: %d: %s\n", errno, strerror(errno));

    printf("Handler for SIGUSR1 (address: %lu/%p) registered successfully!\n",
           (unsigned long) &sigusr1_handler, &sigusr1_handler);
    printf("Handler for SIGUSR2 (address: %lu/%p) registered successfully!\n",
           (unsigned long) &sigusr2_handler, &sigusr2_handler);

    printf("pid %d\n", getpid());
    while(1);

    return 0;
}
