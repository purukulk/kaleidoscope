#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int i;
    for(i = 0; i < 20; i++)
        if(fork() < 0)
            fprintf(stderr, "%d: %s\n", errno, strerror(errno));
    return 0;
}
