#include <linux/module.h>
#include <linux/sched.h>

int __init init_module(void)
{
    printk(KERN_INFO "pid: %d, name: %s\n", current->pid, current->comm);
    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
