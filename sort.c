#include <linux/module.h>
#include <linux/sort.h>

#define ARR_LEN 10

int arr[ARR_LEN];
int num_ele;

int cmp_func(const void *a, const void *b)
{
    if(*(int *) a < *(int *) b)
        return 1;
    else if(*(int *) a > *(int *) b)
        return -1;
    else
        return 0;
}

int init_module(void)
{
    int i;
    if(num_ele != ARR_LEN)
    {
        printk("Error: exactly 10 ints reqiured!\n");
        return 0;
    }
    for(i = 0; i < ARR_LEN; i++)
        printk("%d: %d\n", i, arr[i]);
    sort(arr, ARR_LEN, sizeof(int), &cmp_func, NULL);
    printk("After sorting:\n");
    for(i = 0; i < ARR_LEN; i++)
        printk("%d: %d\n", i, arr[i]);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

module_param_array(arr, int, &num_ele, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(arr, "an integer array");
