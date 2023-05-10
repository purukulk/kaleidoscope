#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 13");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init sighand_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    void (*sighandler)(int);

    if (task == NULL)
        return -ESRCH;

    pr_info("Process: name: %s, pid: %d\n", task->comm, task->pid);

    sighandler = task->sighand->action[SIGUSR1 - 1].sa.sa_handler;
    task->sighand->action[SIGUSR1 - 1].sa.sa_handler = task->sighand->action[SIGUSR2 - 1].sa.sa_handler;
    task->sighand->action[SIGUSR2 - 1].sa.sa_handler = sighandler;

    return 0;
}

static void __exit sighand_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(sighand_init);
module_exit(sighand_exit);
