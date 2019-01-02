#include <linux/module.h>
#include <linux/slab.h>

#define WORD_SIZE 64
#define LEN_STR WORD_SIZE + 16

char *long_to_binary(unsigned long dec)
{
    int i = LEN_STR - 2, skip = 0;
    char *bin = kmalloc(LEN_STR, GFP_KERNEL);
    memset(bin, '0', LEN_STR);
    bin[LEN_STR - 1] = '\0';
    while(dec)
    {
        if(dec % 2)
            bin[i--] = '1';
        else
            bin[i--] = '0';
        dec /= 2;
        skip++;
        if(skip == 4)
        {
            bin[i--] = ' ';
            skip = 0;
        }
    }
    while(i >= 0)
    {
        bin[i--] = '0';
        skip++;
        if(skip == 4)
        {
            bin[i--] = ' ';
            skip = 0;
        }
    }
    return bin;
}

int __init init_module(void)
{
    unsigned long cr0, cr2, cr3, cr4, cr8;
    asm volatile("mov %%cr0,%0\n\t" : "=r"(cr0));
    asm volatile("mov %%cr2,%0\n\t" : "=r"(cr2));
    asm volatile("mov %%cr3,%0\n\t" : "=r"(cr3));
    asm volatile("mov %%cr4,%0\n\t" : "=r"(cr4));
    asm volatile("movq %%cr8,%0" : "=r"(cr8));
    printk("CR0: 0x%lx, CR2: 0x%lx, CR3: 0x%lx, CR4: 0x%lx, CR8: 0x%lx\n", cr0, cr2, cr3,
           cr4, cr8);
    printk("CR0: %s\n", long_to_binary(cr0));
    printk("CR2: %s\n", long_to_binary(cr2));
    printk("CR3: %s\n", long_to_binary(cr3));
    printk("CR4: %s\n", long_to_binary(cr4));
    printk("CR8: %s\n", long_to_binary(cr8));
    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
