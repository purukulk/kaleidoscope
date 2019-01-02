#include <linux/fdtable.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/tty.h>

int __init init_module(void)
{
    struct task_struct *task;

    for_each_process(task)
    {
        printk("\n%5s %5s %15s %10s %10s %10s %10s %10s %5s %5s %5s %5s %10s %5s %10s "
               "%10s %10s\n",
               "PID", "PPID", "Name", "User Time", "Sys Time", "Start Time", "Prio",
               "Static", "Nice", "UID", "GID", "CPU", "flags", "# Files", "Policy",
               "State", "TTY");
        printk("%5d %5d %15s %10llu %10llu %10llu %10d %10d %5d %5u %5u %5d %10X %5d "
               "%10u %10ld %10s\n",
               task->pid, task->parent->pid, task->comm, task->utime / 1000UL,
               task->stime / 1000UL, task->start_time / (60UL * 60UL * 1000000000UL),
               task->prio, task->static_prio, PRIO_TO_NICE(task->static_prio),
               task->cred->uid.val, task->cred->gid.val, task_cpu(task), task->flags,
               task->files->count.counter, task->policy, task->state,
               task->signal->tty ? task->signal->tty->name : "NULL");
    }

    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
