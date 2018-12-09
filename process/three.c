/*
 * Write a module to know the names of processes with pids 0, 1 and 2.
 * Use for_each_process macro defined in linux/sched/signal.h for
 * traversing all the processes. (NOTE: you might have to put some extra
 * effort to print the name of process with pid 0!)
 *
 * Copyright (C) 2018  Sukrit Bhatnagar
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 */


#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>

int init_module(void)
{
    struct task_struct *task;

    printk(KERN_INFO "pid: %d, name: %s\n", init_task.pid, init_task.comm);
    for_each_process(task)
    {
        if(task->pid < 3)
            printk(KERN_INFO "Process: name: %s, pid: %d\n", task->comm, task->pid);
    }

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}
