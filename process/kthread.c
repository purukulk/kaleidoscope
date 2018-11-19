#include<linux/module.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<linux/signal.h>
#include<linux/kthread.h>
#include<linux/delay.h>

struct task_struct *thread;

int thread_func(void *data)
{
    printk("I am a new kernel thread and I am sleeping for 20 seconds!\n");
    msleep(20*1000);
    printk("I am awake now!\n");
    return 0;
}

int init_module(void)
{
    thread = kthread_run(thread_func, NULL, "Kernel Thread!");

    send_sig(SIGKILL, thread, 1);
    
    return 0;
}
void cleanup_module(void)
{
//    see https://stackoverflow.com/a/37844575/1866196 and
//    http://tuxthink.blogspot.com/2014/06/terminating-kernel-thread-using.html 
//    for more on this!
//
//    int ret = kthread_stop(thread);
//    if(!ret)
//        printk(KERN_INFO "Stopping the thread!\n");
    printk(KERN_INFO "Exiting module!\n");
}

MODULE_LICENSE("GPL v2");
