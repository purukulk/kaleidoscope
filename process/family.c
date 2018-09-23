#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>

int pid;

int init_module(void)
{
    struct task_struct *task, *i;

    for_each_process(task)
    {
        if(task->pid == pid)
            break;
    }

    printk(KERN_INFO "Current: name: %s, pid: %d", task->comm, task->pid);
    do
    {
        task = task->parent;
        printk(KERN_INFO "Parent: name: %s, pid: %d\n", task->comm, task->pid);
        
    } while(task->pid != 0);

    list_for_each_entry(i, &task->sibling, sibling)
    {
        printk(KERN_INFO "Sibling: name: %s, pid: %d\n", i->comm, i->pid);
    }

    list_for_each_entry(i, &task->children, children)
    {
        printk(KERN_INFO "Children: name: %s, pid: %d\n", i->comm, i->pid);
    }

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
