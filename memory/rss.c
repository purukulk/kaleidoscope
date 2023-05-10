#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/swap.h>
#include <linux/swapops.h>
#include <asm/cpufeature.h>
#include <asm/page_types.h>
#include <asm/pgtable_64.h>
#include <asm/pgtable_types.h>
#include <linux/mm.h>
#include <linux/mm_types.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 7, Question 5");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init rss_init(void)
{
    unsigned long rss, lrss, address;
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct mm_struct *mm = task->mm;
    struct vm_area_struct *mmap = mm->mmap;
    struct page *page = NULL;
    unsigned long pfn = 0;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    if(task == NULL)
        return -ESRCH;

    rss = get_mm_rss(mm);
    pr_info("Task: name: %s, pid: %d\n", task->comm, task->pid);
    pr_info("RSS = %lu pages OR %lu bytes\n", rss, rss * 4);

    rss = 0;
    do
    {
        if (mmap->vm_flags & VM_PFNMAP)
        {
            mmap = mmap->vm_next;
            continue;
        }

        pgd = mmap->vm_mm->pgd;
        address = mmap->vm_start;
        pgd = pgd_offset(mm, address);
        lrss = 0;
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
                    pfn = pte_pfn(*pte);
                    lrss += PAGE_SIZE;
                }
                pte_unmap(pte);
            }
            address += PAGE_SIZE;

        } while(address < mmap->vm_end);

        pr_info("lrss: %lu\n", lrss / 1024);
        rss += lrss;
        mmap = mmap->vm_next;
    } while(mmap != NULL);

    pr_info("RSS = %lu bytes OR %lu KB\n", rss, rss / 1024);
    return 0;
}

static void __exit rss_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(rss_init);
module_exit(rss_exit);