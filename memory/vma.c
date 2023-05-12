#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 7, Question 3");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 0660);
MODULE_PARM_DESC(pid, "PID of process to be inspected");

static int __init vma_init(void)
{
    int vma_count = 0, vss = 0;
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct mm_struct *mm = task->mm;
    struct vm_area_struct *mmap = mm->mmap;

    if (task == NULL)
        return -1;

    pr_info("Task: name: %s, pid: %d\n", task->comm, task->pid);

    do
    {
        vss += (mmap->vm_end - mmap->vm_start);
        vma_count++;
        mmap = mmap->vm_next;
    } while(mmap != NULL);

    pr_info("VMA Count = %d\n", vma_count);
    pr_info("VSS = %d KB\n", vss >> 10);

    return 0;
}

static void __exit vma_exit(void)
{
    pr_info("Exiting module!\n");
}

module_init(vma_init);
module_exit(vma_exit);