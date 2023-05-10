#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/time.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 12");
MODULE_LICENSE("GPL v2");

static int cpu;
module_param(cpu, int, 00600);
MODULE_PARM_DESC(cpu, "an integer variable");

int thread_func(void *data)
{
    struct timespec64 ts1, ts2;

    pr_info("I am a new kernel thread and I am running for 20 seconds!\n");
    
    ktime_get_ts64(&ts1);
    while(1)
    {
        ktime_get_ts64(&ts2);
        if(ts2.tv_sec >= ts1.tv_sec + 20)
            break;
    }

    pr_info("I am done now!\n");
    return 0;
}

static int __init kthread_cpu_init(void)
{
    struct task_struct *thread;
    thread = kthread_create(thread_func, NULL, "CPU-pinned kthread");
    kthread_bind(thread, cpu);

    if(thread != NULL)
        wake_up_process(thread);

    pr_info("The kthread is running on CPU %d\n", task_cpu(thread));
    return 0;
}

static void __exit kthread_cpu_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(kthread_cpu_init);
module_exit(kthread_cpu_exit);