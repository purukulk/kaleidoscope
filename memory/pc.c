#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 7, Question 4");
MODULE_LICENSE("GPL v2");

static int ppid, cpid;
module_param(ppid, int, 0600);
MODULE_PARM_DESC(ppid, "PID of parent");
module_param(cpid, int, 0600);
MODULE_PARM_DESC(cpid, "PID of child");

static int __init pc_init(void)
{
    int vma_count, vma_size, vss;
    struct task_struct *parent = pid_task(find_get_pid(ppid), PIDTYPE_PID);
    struct task_struct *child = pid_task(find_get_pid(cpid), PIDTYPE_PID);

    struct mm_struct *pmm;
    struct vm_area_struct *pmmap;

    struct mm_struct *cmm;
    struct vm_area_struct *cmmap;

    if (!parent || !child)
    {
        pr_err("Invalid PID(s)!\n");
        return 0;
    }

    pmm = parent->mm;
    pmmap = pmm->mmap;
    cmm = child->mm;
    cmmap = cmm->mmap;

    pr_info("Parent: name: %s, pid: %d\n", parent->comm, parent->pid);
    pr_info("Child: name: %s, pid: %d\n", child->comm, child->pid);

    vma_count = vss = 0;
    pr_info("Printing parent's VMAs...\n");
    do
    {
        vma_size = pmmap->vm_end - pmmap->vm_start;
        vma_count++;
        pr_info("[%d] %lu - %lu: %d\n", vma_count, pmmap->vm_start, pmmap->vm_end, vma_size);
        vss += vma_size;
        pmmap = pmmap->vm_next;
    } while(pmmap != NULL);
    pr_info("Parent's VSS: %d\n", vss);

    vma_count = vss = 0;
    pr_info("Printing child's VMAs...\n");
    do
    {
        vma_size = cmmap->vm_end - cmmap->vm_start;
        vma_count++;
        pr_info("[%d] %lu - %lu: %d\n", vma_count, cmmap->vm_start, cmmap->vm_end, vma_size);
        vss += vma_size;
        cmmap = cmmap->vm_next;
    } while(cmmap != NULL);
    pr_info("Child's VSS: %d\n", vss);

    return 0;
}

static void __exit pc_exit(void)
{
    pr_info("Exiting module!\n");
}

module_init(pc_init);
module_exit(pc_exit);
