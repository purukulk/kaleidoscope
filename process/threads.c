#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 14");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init threads_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct task_struct *thr = task;

    if(task == NULL)
        return -ESRCH;

    pr_info("Task: name: %s, pid: %d\n", task->comm, task->pid);

    for_each_thread(task, thr)
    {
        pr_info("TID: %d, COMM: %10s, MM: %pK, STACK: %pKi, SIGNAL: %pK\n", thr->pid,
               thr->comm, thr->mm, thr->stack, thr->signal);
    }

    return 0;
}

static void __exit threads_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(threads_init);
module_exit(threads_exit);