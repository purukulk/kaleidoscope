#include <linux/module.h>

#define ARR_LEN 10

int arr[ARR_LEN];
int num_ele;

int __init init_module(void)
{
    int i;
    if(num_ele != ARR_LEN)
    {
        printk("Error: exactly 10 ints reqiured!\n");
        return 0;
    }
    for(i = 0; i < ARR_LEN; i++)
        printk("%d: %d\n", i, arr[i]);
    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param_array(arr, int, &num_ele, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(arr, "an integer array");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
