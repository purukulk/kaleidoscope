#include <linux/export.h>
#include <linux/module.h>
#include <linux/threads.h>

extern int pid_max_min;

int __init init_module(void)
{
    printk(KERN_INFO "Maximum value for a pid: %d\n", PID_MAX_DEFAULT);
    printk(KERN_INFO "Minimum value for a pid: %d\n", pid_max_min);
    // printk("Range of reserved pids: %d - %d\n", 0, RESERVED_PIDS);
    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
