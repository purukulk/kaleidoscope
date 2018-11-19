#include<linux/module.h>
#include<linux/pid.h>
#include<linux/sched.h>

int pid;

int init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if(task == NULL)
    {
        printk("task NULL!!\n");
        return 0;
    }
    printk(KERN_INFO "Task: name: %s, pid: %d\n", task->comm, task->pid);
    printk(KERN_INFO "%pK %pK\n", task->mm, task->active_mm);
    printk(KERN_INFO "%d %d\n", task->pid, task->tgid);

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
MODULE_LICENSE("GPL v2");
