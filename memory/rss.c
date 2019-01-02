#include <asm/cpufeature.h>
#include <asm/page_types.h>
#include <asm/pgtable_64.h>
#include <asm/pgtable_types.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/swap.h>
#include <linux/swapops.h>

int pid;

int __init init_module(void)
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
        return -1;

    rss = get_mm_rss(mm);
    printk(KERN_INFO "Task: name: %s, pid: %d\n", task->comm, task->pid);
    printk("RSS = %lu pages OR %lu bytes\n", rss, rss * 4);

    rss = 0;
    do
    {
        if(mmap->vm_flags & VM_PFNMAP)
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
            if(!pmd_bad(*pmd) && !pmd_none(*pmd))
            {
                pte = pte_offset_map(pmd, address);
                if(pte_present(*pte))
                {
                    page = pte_page(*pte);
                    pfn = pte_pfn(*pte);
                    lrss += PAGE_SIZE;
                }
                pte_unmap(pte);
            }
            address += PAGE_SIZE;

        } while(address < mmap->vm_end);
        printk("lrss: %lu\n", lrss / 1024);
        rss += lrss;
        mmap = mmap->vm_next;
    } while(mmap != NULL);

    printk("RSS = %lu bytes OR %lu KB\n", rss, rss / 1024);

    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
