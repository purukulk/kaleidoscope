#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4");
MODULE_LICENSE("GPL v2");

static int __init sizes_init(void)
{
    pr_info("char: %lu\n", sizeof(char));
    pr_info("bool: %lu\n", sizeof(bool));
    pr_info("short: %lu\n", sizeof(short));
    pr_info("int: %lu\n", sizeof(int));
    pr_info("long: %lu\n", sizeof(long));
    pr_info("long long: %lu\n", sizeof(long long));
    pr_info("void *: %lu\n", sizeof(void *));
    return 0;
}

static void __exit sizes_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(sizes_init);
module_exit(sizes_exit);