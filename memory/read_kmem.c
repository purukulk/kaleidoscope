#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <asm/io.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 7");
MODULE_LICENSE("GPL v2");

char str[4096];
char str2[] = "Bhatnagar";
EXPORT_SYMBOL(str);

static int __init read_kmem_init(void)
{
    pr_info("Entering module...\n");
    strcpy(str, "Sukrit");

    pr_info("Address of the string: %s %lu\n", str, (unsigned long) virt_to_phys(str));
    pr_info("Address of the string2: %s %lu\n", str2, (unsigned long) virt_to_phys(str2));
    return 0;
}

static void __exit read_kmem_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(read_kmem_init);
module_exit(read_kmem_exit);