#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 2");
MODULE_LICENSE("GPL v2");

/**
 * You need to be logged in to a tty to see the messages.
 * Try Ctrl + Alt + F3 for tty3
*/

static int __init log_init(void)
{
    pr_emerg("KERN_EMERG log level <0>");
    pr_alert("KERN_ALERT log level <1>");
    pr_crit("KERN_CRIT log level <2>");
    pr_err("KERN_ERR log level <3>");
    pr_warn("KERN_WARN log level <4>");
    pr_notice("KERN_NOTICE log level <5>");
    pr_info("KERN_INFO log level <6>");
    pr_debug("KERN_DEBUG log level <7>");
    return 0;
}

static void __exit log_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(log_init);
module_exit(log_exit);
