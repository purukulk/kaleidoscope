#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pid.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 1");
MODULE_LICENSE("GPL v2");

static int __init proc_values_init(void)
{
    pr_info("Minimum maximum value for a pid: %d\n", pid_max_min);
    pr_info("Maximum maximum value for a pid: %d\n", pid_max_max);
    return 0;
}

static void __exit proc_values_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(proc_values_init);
module_exit(proc_values_exit);