#include<linux/module.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<linux/kernel.h>

int pid;

int init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct task_struct *p;

    printk(KERN_INFO "Task: name: %s, pid: %d\n", task->comm, task->pid);

    printk("task: %pK\n", task);
    printk("children.next: %pK\n", container_of(task->children.next, struct task_struct, sibling));
    printk("children.prev: %pK\n", container_of(task->children.prev, struct task_struct, sibling));
    printk("sibling.next: %pK\n", task->sibling.next);
    printk("sibling.prev: %pK\n", task->sibling.prev);

    list_for_each_entry(p, &task->children, sibling)
    {
        printk("pid: %d, child: %pK, child->sibling.next: %pK\n", p->pid, p, p->sibling.next);
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
