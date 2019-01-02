#include <linux/module.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/time.h>

int n;

struct info
{
    unsigned long num;
    unsigned long sqrt;
    struct list_head list;
};

int __init init_module(void)
{
    int i, t, avg;
    static LIST_HEAD(info_list);
    struct info *node, *next;
    struct timespec t1, t2;

    avg = 0;
    for(i = 0; i < n; i++)
    {
        node = kmalloc(sizeof(struct info), GFP_KERNEL);
        node->num = get_random_long();
        node->sqrt = int_sqrt(node->num);
        INIT_LIST_HEAD(&node->list);

        getnstimeofday(&t1);
        list_add_tail(&node->list, &info_list);
        getnstimeofday(&t2);

        t = t2.tv_nsec - t1.tv_nsec;
        printk("Time taken to insert node #%i: %d usecs", i + 1, t);

        avg += t;
    }
    avg /= n;
    printk("Average time taken for an insertion operation: %d nsecs\n", avg);

    list_for_each_entry_safe_reverse(node, next, &info_list, list)
        kfree(node);

    return 0;
}
void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param(n, int, 00600);
MODULE_PARM_DESC(n, "an integer variable");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
