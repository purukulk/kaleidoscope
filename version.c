#include<linux/module.h>
#include<linux/version.h>

int init_module(void)
{
    int a, b, c;
    printk(KERN_INFO "version code: %d\n", LINUX_VERSION_CODE);
    c = (LINUX_VERSION_CODE << 24) >> 24;
    b = (LINUX_VERSION_CODE << 16) >> 24;
    a = LINUX_VERSION_CODE >> 16;
    printk(KERN_INFO "version: %d.%d.%d\n", a, b, c);
    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}
