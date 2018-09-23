#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>

int init_module(void)
{
    struct task_struct *task;

    printk(KERN_INFO "pid: %d, name: %s\n", init_task.pid, init_task.comm);
    for_each_process(task)
    {
        if(task->pid < 3)
            printk(KERN_INFO "Process: name: %s, pid: %d\n", task->comm, task->pid);
    }

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}
