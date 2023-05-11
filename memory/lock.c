#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/swap.h>
#include <linux/swapops.h>
#include <linux/kernel.h>
#include <asm/cpufeature.h>
#include <asm/page_types.h>
#include <asm/pgtable_64.h>
#include <asm/pgtable_types.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 7, Question 5");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init lock_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct mm_struct *mm;
    struct vm_area_struct *mmap;

    if(task == NULL)
        return -ESRCH;

    mm = task->mm;
    mmap = mm->mmap;
    do
    {
        mmap->vm_flags = mmap->vm_flags & (~(VM_WRITE | VM_MAYWRITE));
        mmap = mmap->vm_next;
    } while(mmap != NULL);

    return 0;
}

static void __exit lock_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(lock_init);
module_exit(lock_exit);