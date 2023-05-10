#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

MODULE_AUTHOR("Aditya Sriram <aweditya@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 14");
MODULE_LICENSE("GPL v2");

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

static int __init cr_init(void)
{
    unsigned long cr0, cr2, cr3, cr4, cr8;
    asm volatile("mov %%cr0,%0\n\t" : "=r"(cr0));
    asm volatile("mov %%cr2,%0\n\t" : "=r"(cr2));
    asm volatile("mov %%cr3,%0\n\t" : "=r"(cr3));
    asm volatile("mov %%cr4,%0\n\t" : "=r"(cr4));
    asm volatile("movq %%cr8,%0" : "=r"(cr8));
    pr_info("CR0: 0x%lx, CR2: 0x%lx, CR3: 0x%lx, CR4: 0x%lx, CR8: 0x%lx\n", cr0, cr2, cr3, cr4, cr8);
    pr_info("CR0: %s\n", long_to_binary(cr0));
    pr_info("CR2: %s\n", long_to_binary(cr2));
    pr_info("CR3: %s\n", long_to_binary(cr3));
    pr_info("CR4: %s\n", long_to_binary(cr4));
    pr_info("CR8: %s\n", long_to_binary(cr8));
    return 0;
}

static void __exit cr_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(cr_init);
module_exit(cr_exit);