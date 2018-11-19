#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

pid_t pid_1[2];
pid_t pid_2[4];
pid_t pid_3[8];
pid_t pid_4[16];

void fork_child3(int i, int j, int k)
{
    int l, s;
    for(l=0;l<2;l++)
    {
        pid_4[i*8+j*4+k*2+l] = fork();
        if(pid_4[i*8+j*4+k*2+l] == 0)
        {
            printf("---- Child %d [%d %d %d %d] (%d)\n", i*8+j*4+k*2+l, i, j, k, l, getpid());
            getchar();
            exit(0);
        }
        else if(pid_4[i*8+j*4+k*2+l] > 0)
            printf("---- (%d) Forked child %d (%d)\n", getpid(), l, pid_4[i*8+j*4+k*2+l]);
    }
    for(l=0; l<2; l++)
        waitpid(pid_4[l], &s, 0);
}
void fork_child2(int i, int j)
{
    int k, s;
    for(k=0;k<2;k++)
    {
        pid_3[i*4+j*2+k] = fork();
        if(pid_3[i*4+j*2+k] == 0)
        {
            printf("--- Child %d [%d %d %d] (%d)\n", i*4+j*2+k, i, j, k, getpid());
            fork_child3(i, j, k);
            exit(0);
        }
        else if(pid_3[i*4+j*2+k] > 0)
            printf("--- (%d) Forked child %d (%d)\n", getpid(), k, pid_3[i*4+j*2+k]);
    }
    for(k=0; k<2; k++)
        waitpid(pid_3[k], &s, 0);
}
void fork_child1(int i)
{
    int j, s;
    for(j=0;j<2;j++)
    {
        pid_2[i*2+j] = fork();
        if(pid_2[i*2+j] == 0)
        {
            printf("-- Child %d [%d %d] (%d)\n", i*2+j, i, j, getpid());
            fork_child2(i, j);
            exit(0);
        }
        else if(pid_2[i*2+j] > 0)
            printf("-- (%d) Forked child %d (%d)\n", getpid(), j, pid_2[i*2+j]);
    }
    for(j=0; j<2; j++)
        waitpid(pid_2[j], &s, 0);
}
int main()
{
    int i, s;
    for(i=0;i<2;i++)
    {
        pid_1[i] = fork();
        if(pid_1[i] == 0)
        {
            printf("- Child %d [%d] (%d)\n", i, i, getpid());
            fork_child1(i);
            exit(0);
        }
        else if(pid_1[i] > 0)
            printf("- (%d) Forked child %d (%d)\n", getpid(), i, pid_1[i]);
    }
    for(i=0; i<2; i++)
        waitpid(pid_1[i], &s, 0);
    return 0;
}
