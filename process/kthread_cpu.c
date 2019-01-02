#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/signal.h>
#include <linux/timekeeping.h>

int cpu;
struct task_struct *thread;

int thread_func(void *data)
{
    struct timespec64 ts1, ts2;

    printk("I am a new kernel thread and I am running for 20 seconds!\n");
    getnstimeofday64(&ts1);
    while(1)
    {
        getnstimeofday64(&ts2);
        if(ts2.tv_sec >= ts1.tv_sec + 20)
            break;
    }
    printk("I am done now!\n");
    return 0;
}
int __init init_module(void)
{
    thread = kthread_create(thread_func, NULL, "CPU-pinned kthread");
    kthread_bind(thread, cpu);

    if(thread != NULL)
        wake_up_process(thread);

    printk(KERN_INFO "The kthread is running on CPU %d\n", task_cpu(thread));

    return 0;
}
void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(cpu, int, 00600);
MODULE_PARM_DESC(cpu, "an integer variable");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
