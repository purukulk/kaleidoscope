#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 10");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID for process");

static int __init sigkill_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if(task == NULL)
        return -ESRCH;

    pr_info("Task: name: %s, pid: %d\n", task->comm, task->pid);

    send_sig(SIGKILL, task, 1);
    return 0;
}

static void __exit sigkill_exit(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_init(sigkill_init);
module_exit(sigkill_exit);