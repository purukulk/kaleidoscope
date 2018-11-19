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

int init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct mm_struct *mm = task->mm;
    struct vm_area_struct *mmap = mm->mmap;
    do
    {
        mmap->vm_flags = mmap->vm_flags & (~(VM_WRITE | VM_MAYWRITE));
        mmap = mmap->vm_next;
    } while(mmap != NULL);

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
MODULE_LICENSE("GPL v2");
