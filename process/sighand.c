#include <linux/mm.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int pid;

int __init init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    void (*sighandler)(int);

    if(task == NULL)
        return -1;

    printk(KERN_INFO "Process: name: %s, pid: %d\n", task->comm, task->pid);

    sighandler = task->sighand->action[SIGUSR1 - 1].sa.sa_handler;
    task->sighand->action[SIGUSR1 - 1].sa.sa_handler =
        task->sighand->action[SIGUSR2 - 1].sa.sa_handler;
    task->sighand->action[SIGUSR2 - 1].sa.sa_handler = sighandler;

    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
