#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 13");
MODULE_LICENSE("GPL v2");

int myval;
module_param(myval, int, 00600);
MODULE_PARM_DESC(myval, "an integer variable");
EXPORT_SYMBOL(myval);

static int __init export_init(void)
{
    pr_info("Entering module export...\n");
    return 0;
}

static void __exit export_exit(void)
{
    pr_info("Exiting module export...\n");
}

module_init(export_init);
module_exit(export_exit);