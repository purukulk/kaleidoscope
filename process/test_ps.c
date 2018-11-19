#include<linux/fdtable.h>
#include<linux/jiffies.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>

int init_module(void)
{
    struct task_struct *task;

    for_each_process(task)
    {
        printk("---------------------------------------------");
        printk("PID: %d\n", task->pid);
        printk("Name: %s\n", task->comm);
        printk("Policy: %u\n", task->policy);
        printk("State: %ld\n", task->state);
        printk("Flags: %X\n", task->flags);
        printk("Min Flt: %lu\n", task->min_flt);
        printk("Maj Flt: %lu\n", task->maj_flt);
        printk("Nr Dirtied: %d\n", task->nr_dirtied);
        printk("Nr Dirtied Pause: %d\n", task->nr_dirtied_pause);
        printk("Ctxt Switch Count: %lu\n", task->nvcsw);
        printk("CtxtI Switch Count: %lu\n", task->nivcsw);
    }
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}
