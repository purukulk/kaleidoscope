#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<linux/delay.h>

int init_module(void)
{
    int count, kcount;
    struct task_struct *task;

    kcount = count = 0;
    for_each_process(task)
    {
        count++;
        if(task->mm == NULL)
            kcount++;
    }
    printk(KERN_INFO "Total count = %d\n", count);
    printk(KERN_INFO "Kernel count = %d\n", kcount);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}
