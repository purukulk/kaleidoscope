#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/stat.h>
#include<linux/types.h>

int pid;
unsigned char c;

int init_module(void)
{
    printk(KERN_INFO "Hello World!\n");
    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye World!\n");
}

module_param(pid, int, S_IRWXU);
module_param(c, unsigned char, S_IRWXU);
