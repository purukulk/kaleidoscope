#include<linux/module.h>
#include<linux/sched.h>

int init_module(void)
{
    printk(KERN_INFO "pid: %d, name: %s\n", current->pid, current->comm);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}
