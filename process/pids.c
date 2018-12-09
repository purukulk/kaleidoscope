#include<linux/module.h>
#include<linux/pid.h>
#include<linux/sched.h>

int pid;

int init_module(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if(task == NULL)
        return 0;

    printk(KERN_INFO "task->pid: %d, task->tgid: %d\n", task->pid, task->tgid);
    printk(KERN_INFO "task->pids[PIDTYPE_PID]: %d\n", task->pids[PIDTYPE_PID].pid->numbers[0].nr);
    printk(KERN_INFO "task->group_leader->pid: %d\n", task->group_leader->pid);
    printk(KERN_INFO "task->group_leader->pids[PIDTYPE_PID]: %d\n", task->group_leader->pids[PIDTYPE_PID].pid->numbers[0].nr);
    printk(KERN_INFO "task->group_leader->pids[PIDTYPE_PGID]: %d\n", task->group_leader->pids[PIDTYPE_PGID].pid->numbers[0].nr);
    printk(KERN_INFO "task->group_leader->pids[PIDTYPE_SID]: %d\n", task->group_leader->pids[PIDTYPE_SID].pid->numbers[0].nr);

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "an integer variable");
MODULE_LICENSE("GPL v2");
