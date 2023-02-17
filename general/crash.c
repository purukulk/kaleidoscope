#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 3");
MODULE_LICENSE("GPL v2");

static int __init crash_init(void)
{
    int *p = NULL;
    pr_alert("%d", *p);
    return 0;
}

static void __exit crash_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(crash_init);
module_exit(crash_exit);