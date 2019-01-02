#include <linux/module.h>

int __init hi(void)
{
    printk(KERN_INFO "Hello World!\n");
    return 0;
}
void __exit bye(void)
{
    printk(KERN_INFO "Goodbye World!\n");
}

module_init(hi);
module_exit(bye);

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
