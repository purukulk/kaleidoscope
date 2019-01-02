#include <linux/module.h>

int myval;
EXPORT_SYMBOL(myval);

int __init init_module(void)
{
    printk(KERN_INFO "Entering module...\n");
    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param(myval, int, 00600);
MODULE_PARM_DESC(myval, "an integer variable");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
