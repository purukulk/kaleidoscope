#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 13");
MODULE_LICENSE("GPL v2");

extern int myval;

static int __init export2_init(void)
{
    printk("Value of myval: %d\n", myval);
    return 0;
}

static void __exit export2_exit(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_init(export2_init);
module_init(export2_exit);