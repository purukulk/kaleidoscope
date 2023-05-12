#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 1");
MODULE_LICENSE("GPL v2");

static int __init hi(void)
{
    pr_info("Name: <your name goes here>\n");
    pr_info("Email ID: <your email ID goes here>\n");
    return 0;
}

static void __exit bye(void)
{
    pr_info("Exiting module...\n");
}

module_init(hi);
module_exit(bye);
