#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 15");
MODULE_LICENSE("GPLv2");

static int __init current_init(void)
{
    struct task_struct *ret = NULL;
    asm ("andl $0xffffe000, %%esp\n\t" : "=r" (ret));

    if (ret == NULL)
        return 0;

    pr_info("Ret Name: %s\n", ret->comm);
    return 0;
}

static void __exit current_exit(void)
{
    pr_info("Exiting module...\n"); 
}

module_init(current_init);
module_exit(current_exit);