#include<linux/module.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>

int pid;

int init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct task_struct *t;

    printk(KERN_INFO "Task: name: %s, pid: %d\n", task->comm, task->pid);

    list_for_each_entry(t, &task->thread_group, thread_group)
    {
        printk("TID: %d, COMM: %10s\n", t->pid, t->comm);
    }
    
    list_for_each_entry(t, &task->signal->thread_head, thread_node)
    {
        printk("TID: %d, COMM: %10s\n", t->pid, t->comm);
    }

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
MODULE_LICENSE("GPL v2");
