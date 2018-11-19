#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
int main()
{
    char *addr1 =
        mmap(NULL, 100, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    char *addr2 =
        mmap(NULL, 200, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
    printf("PID = %d\n", getpid());
    memset(addr1, 'a', 100);
    addr1[99] = '\0';
    memset(addr2, 'b', 200);
    addr2[199] = '\0';
    getchar();
    printf("MMAP 1: %s\n", addr1);
    printf("MMAP 2: %s\n", addr2);
    return 0;
}
