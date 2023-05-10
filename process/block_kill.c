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

static int __init block_kill_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if(task == NULL)
        return -ESRCH;

    printk("Process: name: %s, pid: %d, state: %d\n", task->comm, task->pid, task->__state);

    task->flags |= PF_EXITING;
    return 0;
}

static void __exit block_kill_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(block_kill_init);
module_exit(block_kill_exit);