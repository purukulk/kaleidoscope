#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd, n, ps, i;
    unsigned long pos;
    char buf[7];
    volatile void *kmem;

    pos = atol(argv[1]);
    ps = getpagesize();
    fd = open("/dev/mem", O_RDWR | O_SYNC);

    if (fd == -1)
    {
        fprintf(stderr, "open() error: %d: %s", errno, strerror(errno));
        exit(-1);
    }

    kmem = (char *) mmap(0, ps, PROT_READ | PROT_WRITE, MAP_SHARED, fd, pos/ps * ps);
    //    lseek(fd, pos, SEEK_SET);
    //    n = read(fd, buf, 6);
    //    if(n < 0)
    //    {
    //        fprintf(stderr, "read() error: %d: %s\n", errno, strerror(errno));
    //        exit(-1);
    //    }
    //    buf[n] = '\0';
    //    printf("Value of buf: %s\n", buf);

    if (kmem != MAP_FAILED)
    {
        printf("%s\n", (char *) kmem);
        for(i=0;i<ps;i++)
            printf("%c", *((char *) kmem + i));
    }
    else
    {
        fprintf(stderr, "mmap() error: %d: %s\n", errno, strerror(errno));
    }

    return 0;
}
