#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 7, Question 2");
MODULE_LICENSE("GPL v2");

static int __init numproc_init(void)
{
    int count, kcount;
    struct task_struct *task;

    kcount = count = 0;
    for_each_process(task)
    {
        count++;
        if(task->mm)
            kcount++;
    }
    printk(KERN_INFO "Total count = %d\n", count);
    printk(KERN_INFO "Kernel count = %d\n", kcount);
    return 0;
}

static void __exit numproc_exit(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_init(numproc_init);
module_exit(numproc_exit);