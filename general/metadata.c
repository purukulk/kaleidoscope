#include <linux/module.h>

int __init init_module(void)
{
    printk(KERN_INFO "Entering module...\n");
    return 0;
}
void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

MODULE_DESCRIPTION("does nothing!");
MODULE_VERSION("1.0");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
