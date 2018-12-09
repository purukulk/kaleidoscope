/*
 * Write a module to print the pid and name of the "current" process.
 * Reason about the output that you see.
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

int init_module(void)
{
    printk(KERN_INFO "pid: %d, name: %s\n", current->pid, current->comm);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module!\n");
}
