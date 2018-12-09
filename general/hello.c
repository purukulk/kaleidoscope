#include<linux/module.h>

int hi(void)
{
    printk(KERN_INFO "Hello World!\n");
    return 0;
}
void bye(void)
{
    printk(KERN_INFO "Goodbye World!\n");
}

module_init(hi);
module_exit(bye);
