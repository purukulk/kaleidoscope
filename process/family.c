#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 4");
MODULE_LICENSE("GPL v2");

static int pid = 0;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process whose family is to be printed");

static int __init family_init(void)
{
    struct task_struct *task, *i;

    task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    pr_info("Current: name: %s, pid: %d", task->comm, task->pid);

    i = task;
    do
    {
        i = i->parent;
        pr_info("Parent: name: %s, pid: %d\n", i->comm, i->pid);

    } while(i->pid != 0);

    list_for_each_entry(i, &task->parent->children, sibling)
    {
        pr_info("Sibling: name: %s, pid: %d\n", i->comm, i->pid);
    }

    list_for_each_entry(i, &task->children, sibling)
    {
        pr_info("Children: name: %s, pid: %d\n", i->comm, i->pid);
    }

    return 0;
}

static void __exit family_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(family_init);
module_exit(family_exit);