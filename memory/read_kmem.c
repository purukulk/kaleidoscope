#include<linux/module.h>
#include<linux/mm_types.h>
#include<linux/pid.h>
#include<linux/sched.h>

char str[4096];
char str2[] = "Bhatnagar";
EXPORT_SYMBOL(str);

int init_module(void)
{
    printk(KERN_INFO "Entering module!\n");
    strcpy(str, "Sukrit");
    printk("Address of the string: %lu %lu\n", (unsigned long) str, (unsigned long) virt_to_phys(str));
    printk("Address of the string2: %lu %lu\n", (unsigned long) str2, (unsigned long) virt_to_phys(str2));
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

MODULE_LICENSE("GPL v2");
