#include <linux/module.h>
#include <asm/syscall.h>

int init_module(void)
{
    printk(KERN_ALERT "%d\n", __NR_syscall_max);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n"); 
}
