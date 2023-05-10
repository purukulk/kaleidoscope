#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/spinlock_types.h>
#include <linux/highmem.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <asm/cpufeature.h>
#include <asm/page_types.h>
#include <asm/pgtable.h>
#include <asm/pgtable_64.h>
#include <asm/pgtable_types.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 7, Question 5");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init mmap_init(void)
{
    unsigned long address;
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct mm_struct *mm;
    struct vm_area_struct *mmap;
    struct page *page;
    char *p;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    if(task == NULL)
        return -ESRCH;

    pr_info("Task: name: %s, pid: %d\n", task->comm, task->pid);

    mm = task->mm;
    mmap = mm->mmap;

    do
    {
        pgd = mmap->vm_mm->pgd;
        address = mmap->vm_start;
        pgd = pgd_offset(mm, address);
        do
        {
            p4d = p4d_offset(pgd, address);
            pud = pud_offset(p4d, address);
            pmd = pmd_offset(pud, address);
            if (!pmd_bad(*pmd) && !pmd_none(*pmd))
            {
                pte = pte_offset_map(pmd, address);
                if (pte_present(*pte))
                {
                    page = pte_page(*pte);
                    get_page(page);
                    p = kmap(page);
                    if (p != NULL)
                    {
                        if(p[0] == 'a' && p[1] == 'a' && p[2] == 'a')
                            p[0] = p[1] = p[2] = 'z';
                        else if(p[0] == 'b' && p[1] == 'b' && p[2] == 'b')
                            p[0] = p[1] = p[2] = 'y';
                        kunmap(page);
                    }
                    put_page(page);
                }
            }
            address += PAGE_SIZE;

        } while(address < mmap->vm_end);

        mmap = mmap->vm_next;
    } while(mmap != NULL);

    return 0;
}

static void __exit mmap_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(mmap_init);
module_exit(mmap_exit);