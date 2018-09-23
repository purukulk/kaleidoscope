#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<../fs/exec.c>

int pid;

int init_module(void)
{
    struct task_struct *task;

    for_each_process(task)
    {
        if(task->pid == pid)
            break;
    }

    printk(KERN_INFO "Current: name: %s, pid: %d", task->comm, task->pid);

    set_task_comm(task, "hellooo");

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
