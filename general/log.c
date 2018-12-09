#include<linux/module.h>
#include<linux/kern_levels.h>

int init_module(void)
{
    printk(KERN_EMERG "EMERG String!!");
    printk(KERN_ALERT "ALERT String!!");
    printk(KERN_CRIT "CRIT String!!");
    printk(KERN_ERR "ERR String!!");
    printk(KERN_WARNING "WARNING String!!");
    printk(KERN_NOTICE "NOTICE String!!");
    printk(KERN_INFO "INFO String!!");
    printk(KERN_DEBUG "DEBUG String!!");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n"); 
}
