#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/* Required for the linux version code macro */
#include <generated/uapi/linux/version.h>

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 5 (requires a custom kernel to be built)");
MODULE_LICENSE("GPL v2");

static int __init decode_init(void)
{
    int a, b, c;
    int code = LINUX_VERSION_CODE;
    a = code / (1 << 16);
    code = code % (1 << 16);
    b = code / (1 << 8);
    code = code % (1 << 8);
    c = code;
    pr_info("Kernel version %d.%d.%d decoded from LINUX_VERSION_CODE macro!", a, b, c);
    return 0;
}

static void __exit decode_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(decode_init);
module_exit(decode_exit);
