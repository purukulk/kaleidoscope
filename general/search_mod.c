#include<linux/module.h>
#include<linux/string.h>

char *mname;

int init_module(void)
{
    struct module *m;
    list_for_each_entry(m, &THIS_MODULE->list, list)
    {
        if(!strcmp(m->name, mname))
        {
            printk(KERN_INFO "Name: %s\n", m->name);
            m->init();
        }
    }
    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param(mname, charp, 00600);
MODULE_AUTHOR("Sukrit");
