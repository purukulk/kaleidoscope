#include <linux/fdtable.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 19");
MODULE_LICENSE("GPL v2");

static int pid = 0;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init open_files_init(void)
{
    int i = 0;
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);
    struct files_struct *files;
    struct fdtable *fdt;

    if(task == NULL)
        return -ESRCH;

    files = task->files;
    fdt = files->fdt;

    while(fdt->fd[i] != NULL)
    {
        pr_info("%s\n", fdt->fd[i]->f_path.dentry->d_iname);
        i++;
    }

    return 0;
}

static void __exit open_files_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(open_files_init);
module_exit(open_files_exit);
