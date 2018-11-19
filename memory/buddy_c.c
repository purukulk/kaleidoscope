#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/slab.h>
int init_module(void)
{
    int i, ret;
    struct page *mem = alloc_pages(GFP_KERNEL, NUM_PAGES);

    if(num_ele > ARR_LEN)
    {
        printk("Error: more than 50 elements!\n");
        return 0;
    }

    addr = page_address(mem);
    printk("Address: %pK\n", addr);

    setup_buddy();
    memset(addr, '0', TOTAL_MEM);

    for(i = 0; i < num_ele; i++)
    {
        ret = alloc(root, arr[i], addr);
        if(ret < 0)
        {
            printk("Error: Buddy allocator full!\n");
            break;
        }
        printk("%s\n", (char *) addr);
    }
    //for(i = 0; i < TOTAL_MEM; i++)
    //    printk("[%d] %c", i, *((char *) addr + i));

    return 0;
}

void cleanup_module(void)
{
    delete_tree(root);
    free_pages((unsigned long) addr, NUM_PAGES);
    printk(KERN_INFO "Exiting module...\n");
}

module_param_array(arr, int, &num_ele, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(arr, "an integer array");
