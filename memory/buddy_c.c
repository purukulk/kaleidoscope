#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/slab.h>

static int __init buddy_c_init(void)
{
    int i, ret;
    struct page *mem = alloc_pages(GFP_KERNEL, NUM_PAGES);

    if (num_ele > ARR_LEN)
    {
        pr_info("Error: more than 50 elements!\n");
        return 0;
    }

    addr = page_address(mem);
    pr_info("Address: %pK\n", addr);

    setup_buddy();
    memset(addr, '0', TOTAL_MEM);

    for (i = 0; i < num_ele; i++)
    {
        ret = alloc(root, arr[i], addr);
        if (ret < 0)
        {
            pr_info("Error: Buddy allocator full!\n");
            break;
        }

        pr_info("%s\n", (char *) addr);
    }

    for(i = 0; i < TOTAL_MEM; i++)
        pr_info("[%d] %c", i, *((char *) addr + i));

    return 0;
}

static void __exit buddy_c_exit(void)
{
    delete_tree(root);
    free_pages((unsigned long) addr, NUM_PAGES);
    pr_info("Exiting module...\n");
}

module_param_array(arr, int, &num_ele, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(arr, "an integer array");
