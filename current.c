#include<linux/module.h>
#include<linux/sched.h>

int init_module(void)
{
    struct task_struct *ret = NULL;
    asm("andl $0xffffe000, %%esp\n\t" : "=r" (ret));
    if(ret == NULL)
        return 0;
    printk("Ret Name: %s\n", ret->comm);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n"); 
}
