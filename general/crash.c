#include <linux/module.h>

int init_module(void)
{
    int *p = NULL;
    printk(KERN_ALERT "%d", *p);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
