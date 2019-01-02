#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEVEL_MAX 5
#define left(i) (2 * i + 1)
#define right(i) (2 * i + 2)

pid_t pids[1024];
int *data;

void process(int i)
{
    printf("Thread %d prints %d\n", i, data[i]);
}

void fork_child(int pi, int level)
{
    int s;

    pids[left(pi)] = fork();
    if(pids[left(pi)] == 0)
    {
        level == LEVEL_MAX ? process(left(pi) - (1 << LEVEL_MAX + 1) + 1)
                           : fork_child(left(pi), level + 1);
        exit(0);
    }
    else if(pids[left(pi)] > 0)
        printf("%*s (%d) Forked child %d (%d)\n", level, "", getpid(), 2, pids[left(pi)]);

    pids[right(pi)] = fork();
    if(pids[right(pi)] == 0)
    {
        level == LEVEL_MAX ? process(right(pi) - (1 << LEVEL_MAX + 1) + 1)
                           : fork_child(right(pi), level + 1);
        exit(0);
    }
    else if(pids[right(pi)] > 0)
        printf("%*s (%d) Forked child %d (%d)\n", level, "", getpid(), 1,
               pids[right(pi)]);

    waitpid(pids[left(pi)], &s, 0);
    waitpid(pids[right(pi)], &s, 0);
}
int main()
{
    int i, s;
    data = calloc(1 << LEVEL_MAX + 1, sizeof(int));
    for(i = 0; i < 1 << LEVEL_MAX + 1; i++)
        data[i] = i;
    fork_child(0, 0);
    return 0;
}
