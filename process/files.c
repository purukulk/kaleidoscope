#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>
#include<linux/fdtable.h>

int pid;

int init_module(void)
{
    int i;
    struct task_struct *task;
    struct files_struct *files;
    //struct file *file;

    for_each_process(task)
    {
        if(task->pid == pid)
        {
            files = task->files;
            for(i = 0; i < files->count.counter; i++)
            {
                printk(KERN_INFO "%s\n", files->fd_array[i]->f_path.dentry->d_iname);
            }
            break;
        }
    }

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
