#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 8");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID for process");

void go_down(struct task_struct *task, int level)
{
    struct task_struct *t;

    if (level == 0)
        pr_info("%s (%d)\n", task->comm, task->pid);
    else if (level == 1)
        pr_info("-%s (%d)\n", task->comm, task->pid);
    else if (level == 2)
        pr_info("--%s (%d)\n", task->comm, task->pid);
    else if (level == 3)
        pr_info("---%s (%d)\n", task->comm, task->pid);
    else if(level == 4)
        pr_info("----%s (%d)\n", task->comm, task->pid);
    else if (level == 5)
        pr_info("-----%s (%d)\n", task->comm, task->pid);
    else
        return;

    list_for_each_entry(t, &task->children, sibling)
    {
        go_down(t, level + 1);
    }
}

static int __init pstree_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if (task == NULL)
        return -ESRCH;

    go_down(task, 0);

    return 0;
}

static void __exit pstree_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(pstree_init);
module_exit(pstree_exit);