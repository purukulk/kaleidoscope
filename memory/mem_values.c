#include <asm/page_types.h>
#include <linux/module.h>

int __init init_module(void)
{
    printk("Page table levels: %d\n", CONFIG_PGTABLE_LEVELS);
    printk("PAGE Shift: %d\n", PAGE_SHIFT);
    printk("PAGE Size: %lu KB\n", PAGE_SIZE / 1024);
    printk("HUGE PAGE Shift: %d\n", HPAGE_SHIFT);
    printk("HUGE PAGE Size: %lu KB, %lu MB\n", HPAGE_SIZE >> 10, HPAGE_SIZE >> 20);
    printk("PMD Shift: %d\n", PMD_SHIFT);
    printk("PMD PAGE Size: %lu KB, %lu MB\n", PMD_SIZE >> 10, PMD_SIZE >> 20);
    printk("PUD PAGE Shift: %d\n", PUD_SHIFT);
    printk("PUD PAGE Size: %lu KB, %lu MB\n", PUD_SIZE >> 10, PUD_SIZE >> 20);
    printk("PGDIR PAGE Shift: %d\n", PGDIR_SHIFT);
    printk("PGDIR PAGE Size: %lu KB, %lu MB, %lu GB\n", PGDIR_SIZE >> 10,
           PGDIR_SIZE >> 20, PGDIR_SIZE >> 30);
    printk("Entries per PTE: %d\n", PTRS_PER_PTE);
    printk("Entries per PMD: %d\n", PTRS_PER_PMD);
    printk("Entries per PUD: %d\n", PTRS_PER_PUD);
    printk("Entries per PGD: %d\n", PTRS_PER_PGD);
    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
