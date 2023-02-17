#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define LEN 10

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 7");
MODULE_LICENSE("GPL v2");

static int arr[LEN];
static int size;

/**
 * Pass name, type and reference to variable that
 * will store number of arguments passed
*/
module_param_array(arr, int, &size, 0000);
MODULE_PARM_DESC(arr, "Integer array");

static int __init array_init(void)
{
    int i;
    if (size != LEN)
    {
        pr_err("Exactly %d integers required!", LEN);
    }
    else
    {
        for(i = 0; i < LEN; ++i)
            pr_info("%d: %d", i, arr[i]);
    }
    return 0;
}

static void __exit array_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(array_init);
module_exit(array_exit);