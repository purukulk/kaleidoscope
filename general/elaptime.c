#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>
#include <linux/slab.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 10");
MODULE_LICENSE("GPL v2");

static struct info
{
    unsigned long num;
    unsigned long sqrt;
    struct list_head list;
} *entry, *n;

static int len;
module_param(len, int, 0000);
MODULE_PARM_DESC(len, "Number of nodes to add to the linked list");

static int __init list_init(void)
{
    int i;
    u64 t1, t2, avg=0;
    struct list_head info_list;
    INIT_LIST_HEAD(&info_list);

    for (i = 0; i < len; ++i)
    {
        entry = kmalloc(sizeof(struct info *), GFP_KERNEL);
        entry->num = get_random_long();
        entry->sqrt = int_sqrt(entry->num);
        INIT_LIST_HEAD(&entry->list);

        t1 = ktime_get_ns();
        list_add_tail(&entry->list, &info_list);
        t2 = ktime_get_ns();

        pr_info("Time to insert entry #%d: %lld nsecs\n", i+1, t2-t1);

        avg += t2 - t1;
    }
    avg /= len;
    pr_info("Average time to insert = %lld\n", avg);

    list_for_each_entry_safe_reverse(entry, n, &info_list, list)
    {
        kfree(entry);
    }

    return 0;
}

static void __exit list_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(list_init);
module_exit(list_exit);
