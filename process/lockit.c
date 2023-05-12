#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 15");
MODULE_LICENSE("GPL v2");

static int pid = 0;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init lockit_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if(task == NULL)
        return -ESRCH;

    pr_info("Process: name: %s, pid: %d\n", task->comm, task->pid);

    task_lock(task);
    return 0;
}

static void __exit lockit_exit(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    task_unlock(task);
    printk(KERN_INFO "Exiting module!\n");
}

module_init(lockit_init);
module_exit(lockit_exit);