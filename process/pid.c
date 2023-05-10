#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 5");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init pid_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if (task == NULL)
        return -ESRCH;

    pr_info("Task: name: %s, pid: %d\n", task->comm, task->pid);
    return 0;
}

static void __exit pid_exit(void)
{
    pr_info(KERN_INFO "Exiting module...\n");
}

module_init(pid_init);
module_exit(pid_exit);