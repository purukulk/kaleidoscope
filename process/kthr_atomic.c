#include<linux/module.h>
#include<linux/pid.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<linux/signal.h>
#include<linux/kthread.h>

#define str(x) #x

unsigned long long a, crit;

int thread_func(void *data)
{
    int i;
    for(i = 0; i < 10000; i++)
    {
        a += 10;
        a *= a;
        a /= a;
        a -= 10;
        crit += a;
    }
    return 0;
}

int init_module(void)
{
    int i;
    struct task_struct *thread[50];
    for(i = 0; i < 50; i++)
        thread[i] = kthread_run(thread_func, NULL, "Kernel Thread "str(i));

    printk("Critical: %llu %llu\n", a, crit);
    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

MODULE_LICENSE("GPL v2");
