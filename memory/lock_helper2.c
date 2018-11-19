#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>

#define LEN 100000
typedef unsigned long long llu;

int main()
{
    int i, p;
    srand(time(NULL));
    printf("Process started with pid %d\n", getpid());
    getchar();
    char *arr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
    p = mprotect(arr, 4096, PROT_NONE);
    if(p == -1)
        printf("mprotect() error: %d: %s\n", errno, strerror(errno));
    for(i = 0; i < 4096; i++)
        arr[i] = rand();
    munmap(arr, 4096);
    return 0;
}
