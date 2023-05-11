#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 16");
MODULE_LICENSE("GPL v2");

static int pid = 0;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init exit_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if (task == NULL)
        return -ESRCH;

    pr_info("Process: name: %s, pid: %d\n", task->comm, task->pid);

    task_lock(task);
    return 0;
}

static void __exit exit_exit(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    
    if (task == NULL)
        return;
    
    pr_info("exit_state: %d\n", task->exit_state);
    pr_info("exit_code: %d\n", task->exit_code);
    pr_info("exit_signal: %d\n", task->exit_signal);
    pr_info("pdeath_signal: %d\n", task->pdeath_signal);

    task_unlock(task);
    pr_info("Exiting module...\n");
}

module_init(exit_init);
module_exit(exit_exit);