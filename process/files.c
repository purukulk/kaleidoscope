#include <linux/fdtable.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int pid;

int __init init_module(void)
{
    int i = 0;
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct files_struct *files;
    struct fdtable *fdt;

    if(task == NULL)
        return -1;

    files = task->files;
    fdt = files->fdt;

    while(fdt->fd[i] != NULL)
    {
        printk(KERN_INFO "%s\n", fdt->fd[i]->f_path.dentry->d_iname);
        i++;
    }

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
