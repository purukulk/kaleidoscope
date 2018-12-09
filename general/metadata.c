#include<linux/module.h>

int init_module(void)
{
    printk(KERN_INFO "Entering module...\n");
    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sukrit");
MODULE_DESCRIPTION("does nothing!");
MODULE_VERSION("1.0");
