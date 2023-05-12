#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 11");
MODULE_LICENSE("GPL v2");

int thread_func(void *data)
{
    pr_info("I am a new kernel thread and I am sleeping for 20 seconds!\n");
    msleep(20 * 1000);
    pr_info("I am awake now!\n");
    return 0;
}

static int __init kthread_init(void)
{
    struct task_struct *thread;
    thread = kthread_run(thread_func, NULL, "Kernel Thread!");

    send_sig(SIGKILL, thread, 1);
    return 0;
}

static void __exit kthread_exit(void)
{
    //    see https://stackoverflow.com/a/37844575/1866196 for more on this!
    //    int ret = kthread_stop(thread);
    //    if(!ret)
    //        printk(KERN_INFO "Stopping the thread!\n");
    pr_info(KERN_INFO "Exiting module...\n");
}

module_init(kthread_init);
module_exit(kthread_exit);
