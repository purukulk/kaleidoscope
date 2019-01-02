#include <linux/module.h>

int init_module(void)
{
    printk(KERN_INFO "char: %lu\n", sizeof(char));
    printk(KERN_INFO "bool: %lu\n", sizeof(bool));
    printk(KERN_INFO "short: %lu\n", sizeof(short));
    printk(KERN_INFO "int: %lu\n", sizeof(int));
    printk(KERN_INFO "long: %lu\n", sizeof(long));
    printk(KERN_INFO "long long: %lu\n", sizeof(long long));
    printk(KERN_INFO "void *: %lu\n", sizeof(void *));
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
