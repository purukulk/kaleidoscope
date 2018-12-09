#include<linux/module.h>

extern int myval;

int init_module(void)
{
    printk("Value of myval: %d\n", myval);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n"); 
}
