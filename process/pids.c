#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 6, Question 14");
MODULE_LICENSE("GPL v2");

static int pid;
module_param(pid, int, 00600);
MODULE_PARM_DESC(pid, "PID of process");

static int __init pids_init(void)
{
    struct task_struct *task = pid_task(find_get_pid(pid), PIDTYPE_PID);

    if(task == NULL)
       return -ESRCH;

    pr_info("task->pid: %d, task->tgid: %d\n", task->pid, task->tgid);
    pr_info("task->thread_pid[PIDTYPE_PID]: %d\n", pid_nr(&task->thread_pid[PIDTYPE_PID]));
    pr_info("task->thread_pid[PIDTYPE_PGID]: %d\n", pid_nr(&task->thread_pid[PIDTYPE_PGID]));
    pr_info("task->thread_pid[PIDTYPE_SID]: %d\n", pid_nr(&task->thread_pid[PIDTYPE_SID]));
    pr_info("task->group_leader->pid: %d\n", task->group_leader->pid);
    pr_info("task->group_leader->thread_pid[PIDTYPE_PID]: %d\n", pid_nr(&task->group_leader->thread_pid[PIDTYPE_PID]));
    pr_info("task->group_leader->thread_pid[PIDTYPE_PGID]: %d\n", pid_nr(&task->group_leader->thread_pid[PIDTYPE_PGID]));
    pr_info("task->group_leader->thread_pid[PIDTYPE_SID]: %d\n", pid_nr(&task->group_leader->thread_pid[PIDTYPE_SID]));
    return 0;
}

static void __exit pids_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(pids_init);
module_exit(pids_exit);