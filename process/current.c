#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 2");
MODULE_LICENSE("GPL v2");

static int __init current_init(void)
{
    pr_info(KERN_INFO "pid: %d, name: %s\n", current->pid, current->comm);
    return 0;
}

static void __exit current_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(current_init);
module_exit(current_exit);