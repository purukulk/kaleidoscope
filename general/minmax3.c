#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 4");
MODULE_LICENSE("GPL v2");

/* Module parameters */
static int a, b, c;
module_param(a, int, 0660);
MODULE_PARM_DESC(a, "First integer variable to be compared");
module_param(b, int, 0660);
MODULE_PARM_DESC(b, "Second integer variable to be compared");
module_param(c, int, 0660);
MODULE_PARM_DESC(c, "Third integer variable to be compared");

static int __init minmax_init(void)
{
    pr_info("Smallest value: %d\n", min3(a, b, c));
    pr_info("Largest value: %d\n", max3(a, b, c));
    return 0;
}

static void __exit minmax_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(minmax_init);
module_exit(minmax_exit);