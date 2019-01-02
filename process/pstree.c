#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int pid;

void go_down(struct task_struct *task, int level)
{
    struct task_struct *t;

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


    list_for_each_entry(t, &task->children, sibling)
    {
        go_down(t, level + 1);
    }
}

int __init init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if(task == NULL)
        return -1;

    go_down(task, 0);

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
