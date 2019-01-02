#include <linux/mm_types.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>

int pid;

int __init init_module(void)
{
    int vma_count = 0, vss = 0;
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct mm_struct *mm = task->mm;
    struct vm_area_struct *mmap = mm->mmap;

    if(task == NULL)
        return -1;

    printk(KERN_INFO "Task: name: %s, pid: %d\n", task->comm, task->pid);

    do
    {
        vss += (mmap->vm_end - mmap->vm_start);
        vma_count++;
        mmap = mmap->vm_next;
    } while(mmap != NULL);

    printk("VMA Count = %d\n", vma_count);
    printk("VSS = %d KB\n", vss >> 10);

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
