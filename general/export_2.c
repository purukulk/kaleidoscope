#include <linux/module.h>

extern int myval;

int __init init_module(void)
{
    printk("Value of myval: %d\n", myval);
    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
