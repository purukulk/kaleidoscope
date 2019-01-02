#include <linux/mm_types.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>

int ppid, cpid;

int __init init_module(void)
{
    int vma_count, vma_size, vss;
    struct task_struct *parent = pid_task(find_get_pid(ppid), PIDTYPE_PID);
    struct task_struct *child = pid_task(find_get_pid(cpid), PIDTYPE_PID);
    struct mm_struct *pmm;
    struct vm_area_struct *pmmap;
    struct mm_struct *cmm;
    struct vm_area_struct *cmmap;

    if(!parent || !child)
    {
        printk("Error: invalid PID(s)!\n");
        return 0;
    }

    pmm = parent->mm;
    pmmap = pmm->mmap;
    cmm = child->mm;
    cmmap = cmm->mmap;

    printk(KERN_INFO "Parent: name: %s, pid: %d\n", parent->comm, parent->pid);
    printk(KERN_INFO "Child: name: %s, pid: %d\n", child->comm, child->pid);

    vma_count = vss = 0;
    printk("Parent's VMAs\n");
    do
    {
        vma_size = pmmap->vm_end - pmmap->vm_start;
        vma_count++;
        printk("[%d] %lu - %lu: %d\n", vma_count, pmmap->vm_start, pmmap->vm_end,
               vma_size);
        vss += vma_size;
        pmmap = pmmap->vm_next;
    } while(pmmap != NULL);
    printk("Parent's VSS: %d\n", vss);

    vma_count = vss = 0;
    printk("Child's VMAs\n");
    do
    {
        vma_size = cmmap->vm_end - cmmap->vm_start;
        vma_count++;
        printk("[%d] %lu - %lu: %d\n", vma_count, cmmap->vm_start, cmmap->vm_end,
               vma_size);
        vss += vma_size;
        cmmap = cmmap->vm_next;
    } while(cmmap != NULL);
    printk("Child's VSS: %d\n", vss);

    return 0;
}

void __exit cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(ppid, int, 00600);
MODULE_PARM_DESC(ppid, "an integer variable");
module_param(cpid, int, 00600);
MODULE_PARM_DESC(cpid, "an integer variable");

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_LICENSE("GPL v2");
