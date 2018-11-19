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
    while(1)
    {
        llu *arr = calloc(LEN, sizeof(llu));
        for(i = 0; i < LEN; i++)
            arr[i] = rand();
        free(arr);
    }
    return 0;
}
