#include<linux/module.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>

int pid;

void go_down(struct task_struct *task, int level)
{
    struct task_struct *t;
    //struct list_head *l;

    if(level == 6)
        return;

    if(level == 0)
        printk("%s (%d)\n", task->comm, task->pid);
    else if(level == 1)
        printk("-%s (%d)\n", task->comm, task->pid);
    else if(level == 2)
        printk("--%s (%d)\n", task->comm, task->pid);
    else if(level == 3)
        printk("---%s (%d)\n", task->comm, task->pid);
    else if(level == 4)
        printk("----%s (%d)\n", task->comm, task->pid);
    else if(level == 5)
        printk("-----%s (%d)\n", task->comm, task->pid);
    
    
    //task_lock(task);

    list_for_each_entry(t, &task->children, sibling)
    //list_for_each(l, &task->children)
    {
        //t = list_entry(l, struct task_struct, sibling);
        //printk("%d %s\n", t->pid, t->comm);
        go_down(t, level+1);
    }

    //task_unlock(task);
}

int init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    go_down(task, 0);

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
MODULE_LICENSE("GPL v2");
