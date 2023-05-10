#include <linux/fdtable.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/tty.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 6");
MODULE_LICENSE("GPL v2");

static int __init ps_init(void)
{
    struct task_struct *task;

    for_each_process(task)
    {
        pr_info("\n%5s %5s %15s %10s %10s %10s %10s %10s %5s %5s %5s %5s %10s %5s %10s "
               "%10s %10s\n",
               "PID", "PPID", "Name", "User Time", "Sys Time", "Start Time", "Prio",
               "Static", "Nice", "UID", "GID", "CPU", "flags", "# Files", "Policy",
               "State", "TTY");
        pr_info("%5d %5d %15s %10llu %10llu %10llu %10d %10d %5d %5u %5u %5d %10X %5d "
               "%10u %10d %10s\n",
               task->pid, task->parent->pid, task->comm, task->utime / 1000UL,
               task->stime / 1000UL, task->start_time / (60UL * 60UL * 1000000000UL),
               task->prio, task->static_prio, PRIO_TO_NICE(task->static_prio),
               task->cred->uid.val, task->cred->gid.val, task_cpu(task), task->flags,
               task->files->count.counter, task->policy, task->__state,
               task->signal->tty ? task->signal->tty->name : "NULL");
    }

    return 0;
}

static void __exit ps_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(ps_init);
module_exit(ps_exit);