#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/slab.h>

#define ARR_LEN 50
#define NUM_PAGES 4
#define TOTAL_MEM NUM_PAGES *PAGE_SIZE
#define TOTAL_MEM_ORDER 14
#define MIN_ALLOC_SIZE 64

struct node
{
    unsigned int size;
    unsigned int len;
    bool full;
    struct node *left;
    struct node *right;
} * root;

void *addr;
int arr[ARR_LEN];
int num_ele;
int int_frag;

void setup_buddy(void);

void setup_buddy()
{
    root = kzalloc(sizeof(struct node), GFP_KERNEL);
    root->size = TOTAL_MEM;
}

int alloc(struct node *n, int size, char *addr)
{
    int ret = -1;

    if(n->full == true || n->size < size)
        return -1;

    if((size > n->size / 2 || n->size == MIN_ALLOC_SIZE)
            && n->left == NULL && n->right == NULL)
    {
        n->full = true;
        n->len = size;
        int_frag += n->size - size;
        memset(addr, '1', size);
        return 0;
    }

    if(n->left == NULL)
    {
        n->left = kzalloc(sizeof(struct node), GFP_KERNEL);
        n->left->size = n->size / 2;
        n->right = kzalloc(sizeof(struct node), GFP_KERNEL);
        n->right->size = n->size / 2;
        if(alloc(n->left, size, addr) == 0)
            ret = 0;
    }

    if(ret != 0 && n->left->full != true)
        if(alloc(n->left, size, addr) == 0)
            ret = 0;

    if(ret != 0 && alloc(n->right, size, addr + n->left->size) == 0)
        ret = 0;

    if(n->left->full && n->right->full)
        n->full = true;

    return ret;
}

void print_tree(struct node *root)
{
    struct node **q = kzalloc(5000 * sizeof(struct node *), GFP_KERNEL), *n;
    int f, r;
    f = r = 0;
    q[r++] = root;
    while(f != r)
    {
        n = q[f++];
        if(n == NULL)
            continue;
        if(n->left != NULL)
            q[r++] = n->left;
        if(n->right != NULL)
            q[r++] = n->right;
        if(n->left && n->right && n->left->full && n->right->full)
            printk("Split & full (%u)\n", n->size);
        else if(n->left || n->right)
            printk("Split (%u)\n", n->size);
        else
            printk("%u (%u)\n", n->len, n->size);
    }
}

int __init init_module(void)
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
    }

    print_tree(root);
    
    printk("Internal fragmentation: %d bytes out of %lu bytes.\n", int_frag, TOTAL_MEM);

    return 0;
}

void delete_tree(struct node *root)
{
    if(root == NULL)
        return;

    delete_tree(root->left);
    delete_tree(root->right);
    kfree(root);
}

void __exit cleanup_module(void)
{
    delete_tree(root);
    free_pages((unsigned long) addr, NUM_PAGES);
    printk(KERN_INFO "Exiting module...\n");
}

module_param_array(arr, int, &num_ele, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(arr, "an integer array");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
