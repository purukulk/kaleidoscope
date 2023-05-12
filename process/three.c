#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 3");
MODULE_LICENSE("GPL v2");

static int __init three_init(void)
{
    struct task_struct *task;

    pr_info("pid: %d, name: %s\n", init_task.pid, init_task.comm);
    for_each_process(task)
    {
        if(task->pid < 3)
            pr_info("Process: name: %s, pid: %d\n", task->comm, task->pid);
    }

    return 0;
}

static void __exit three_exit(void)
{
    pr_info("Exiting module!\n");
}

module_init(three_init);
module_exit(three_exit);