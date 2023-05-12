#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 10");
MODULE_LICENSE("GPL v2");

static char *module_name;
module_param(module_name, charp, 0660);
MODULE_PARM_DESC(module_name, "Name of module to search for");

static int __init searchmod_init(void)
{
    struct module *m;

    if(module_name == NULL)
        return -1;

    list_for_each_entry(m, &THIS_MODULE->list, list)
    {
        if(!strcmp(m->name, module_name))
        {
            pr_info("Name: %s\n", m->name);
            m->init();
        }
    }
    return 0;
}

static void __exit searchmod_exit(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_init(searchmod_init);
module_exit(searchmod_exit);