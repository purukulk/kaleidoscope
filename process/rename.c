#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 7");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init rename_init(void)
{
    struct task_struct *task;

    for_each_process(task)
    {
        if (task->pid == pid)
            break;
    }

    if (task == &init_task)
        return -EPERM;

    pr_info("Current: name: %s, pid: %d", task->comm, task->pid);

    task_lock(task);
    strcpy(task->comm, "ola");
    task_unlock(task);

    pr_info("Current: name: %s, pid: %d", task->comm, task->pid);
    return 0;
}

static void __exit rename_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(rename_init);
module_exit(rename_exit);