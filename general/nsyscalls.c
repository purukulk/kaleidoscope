#include <asm/syscall.h>
#include <linux/module.h>

int init_module(void)
{
    printk(KERN_ALERT "%d\n", __NR_syscall_max);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
