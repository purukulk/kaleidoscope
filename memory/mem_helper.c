#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LEN 100000
typedef unsigned long long llu;

int main()
{
    int i;
    llu *arr = calloc(LEN, sizeof(llu));
    srand(time(NULL));
    printf("Process started with pid %d\n", getpid());
    while(1)
    {
        for(i = 0; i < LEN; i++)
            arr[i] = rand();
        //getchar();
    }
    return 0;
}
