#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int pid;

int __init init_module(void)
{
    struct task_struct *task;

    for_each_process(task)
    {
        if(task->pid == pid)
            break;
    }

    if(task == &init_task)
        return -1;

    printk(KERN_INFO "Current: name: %s, pid: %d", task->comm, task->pid);

    // set_task_comm(task, "hellooo");

    task_lock(task);

    strcpy(task->comm, "hellooo");

    task_unlock(task);

    printk(KERN_INFO "Current: name: %s, pid: %d", task->comm, task->pid);

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
