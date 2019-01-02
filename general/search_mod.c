#include <linux/module.h>
#include <linux/string.h>

char *mname;

int __init init_module(void)
{
    struct module *m;

    if(mname == NULL)
        return -1;

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
void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param(mname, charp, 00600);
MODULE_PARM_DESC(mname, "a string");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
