#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd1, fd2, ret;
    fd1 = open("tmp1.txt", O_RDONLY | O_CREAT);
    if (fd1 == -1)
    {
        fprintf(stderr, "open() error: %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    fd2 = open("tmp2.txt", O_RDONLY | O_CREAT);
    if (fd2 == -1)
    {
        fprintf(stderr, "open() error: %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    getchar();

    ret = close(fd1);
    if (ret == -1)
    {
        fprintf(stderr, "open() error: %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    ret = close(fd2);
    if (ret == -1)
    {
        fprintf(stderr, "open() error: %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return 0;
}
