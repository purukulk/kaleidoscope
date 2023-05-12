#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/page_types.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Solution to Chapter 7, Problem 1");
MODULE_LICENSE("GPL v2");

static int __init test_init(void)
{
    pr_info("Page table levels: %d\n", CONFIG_PGTABLE_LEVELS);
    pr_info("PAGE Shift: %d\n", PAGE_SHIFT);
    pr_info("PAGE Size: %lu KB\n", PAGE_SIZE / 1024);
    pr_info("HUGE PAGE Shift: %d\n", HPAGE_SHIFT);
    pr_info("HUGE PAGE Size: %lu KB, %lu MB\n", HPAGE_SIZE >> 10, HPAGE_SIZE >> 20);
    pr_info("PMD Shift: %d\n", PMD_SHIFT);
    pr_info("PMD PAGE Size: %lu KB, %lu MB\n", PMD_SIZE >> 10, PMD_SIZE >> 20);
    pr_info("PUD PAGE Shift: %d\n", PUD_SHIFT);
    pr_info("PUD PAGE Size: %lu KB, %lu MB\n", PUD_SIZE >> 10, PUD_SIZE >> 20);
    pr_info("PGDIR PAGE Shift: %d\n", PGDIR_SHIFT);
    pr_info("PGDIR PAGE Size: %lu KB, %lu MB, %lu GB\n", PGDIR_SIZE >> 10,
           PGDIR_SIZE >> 20, PGDIR_SIZE >> 30);
    pr_info("Entries per PTE: %d\n", PTRS_PER_PTE);
    pr_info("Entries per PMD: %d\n", PTRS_PER_PMD);
    pr_info("Entries per PUD: %d\n", PTRS_PER_PUD);
    pr_info("Entries per PGD: %d\n", PTRS_PER_PGD);
    return 0;
}

static void __exit test_exit(void)
{
    pr_info("Exiting module!\n");
}

module_init(test_init);
module_exit(test_exit);