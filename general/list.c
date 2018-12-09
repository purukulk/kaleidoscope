#include<linux/module.h>
#include<linux/random.h>
#include<linux/slab.h>

int n;

struct info
{
    unsigned long num;
    unsigned long sqrt;
    struct list_head list;
};

int init_module(void)
{
    int i;
    static LIST_HEAD(info_list);
    struct info *node, *next;

    for(i = 0; i < n; i++)
    {
        node = kmalloc(sizeof(struct info), GFP_KERNEL);
        node->num = get_random_long();
        node->sqrt = int_sqrt(node->num);
        INIT_LIST_HEAD(&node->list);

        list_add_tail(&node->list, &info_list);
        
        printk(KERN_INFO "Inserted: num: %lu, sqrt: %lu\n", node->num, node->sqrt);
    }

    list_for_each_entry_safe_reverse(node, next, &info_list, list)
    {
        printk(KERN_INFO "Deleted: num: %lu, sqrt: %lu\n", node->num, node->sqrt);
        kfree(node);
    }

    return 0;
}
void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param(n, int, 00600);
MODULE_PARM_DESC(n, "an integer variable");
