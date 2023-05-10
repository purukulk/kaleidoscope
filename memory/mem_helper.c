#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LEN 100000

int main()
{
    int i;
    unsigned long long *arr = calloc(LEN, sizeof(unsigned long long));

    srand(time(NULL));
    printf("Process started with pid %d\n", getpid());

    while(1)
    {
        for(i = 0; i < LEN; i++)
            arr[i] = rand();
    }

    return 0;
}
