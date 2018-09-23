#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/stat.h>
#include<linux/init.h>
#include<linux/types.h>

int a, b, c;
int init_module(void)
{
    printk(KERN_INFO "smallest value: %d\n", min3(a, b, c));
    printk(KERN_INFO "largest value: %d\n", max3(a, b, c));
    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param(a, int, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(a, "an integer variable");
module_param(b, int, 00600);
MODULE_PARM_DESC(b, "another integer variable");
module_param(c, int, 00600);
MODULE_PARM_DESC(c, "yet another integer variable");
