#include<linux/fdtable.h>
#include<linux/jiffies.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<asm-generic/param.h>

int pid;

int init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    printk("%d %d %lu\n", HZ, USER_HZ, TICK_NSEC);
    printk("%llu %llu\n", task->vtime.utime, task->vtime.stime);
    printk("---------------------------------------------");
    printk("PID: %d\n", task->pid);
    printk("Name: %s\n", task->comm);
    printk("Policy: %u\n", task->policy);
    printk("Utime: %llu %lu s\n", task->utime, jiffies_to_clock_t(task->utime));
    printk("Stime: %llu %lu s\n", task->stime, jiffies_to_clock_t(task->stime));
    printk("Gtime: %llu %lu s\n", task->gtime, jiffies_to_clock_t(task->gtime));
    printk("State: %ld\n", task->state);
    printk("Flags: %X\n", task->flags);
    printk("Min Flt: %lu\n", task->min_flt);
    printk("Maj Flt: %lu\n", task->maj_flt);
    printk("Nr Dirtied: %d\n", task->nr_dirtied);
    printk("Nr Dirtied Pause: %d\n", task->nr_dirtied_pause);
    printk("Ctxt Switch Count: %lu\n", task->nvcsw);
    printk("CtxtI Switch Count: %lu\n", task->nivcsw);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
MODULE_LICENSE("GPL v2");
