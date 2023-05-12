#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Sukrit Bhatnagar <skrtbhtngr@gmail.com>");
MODULE_DESCRIPTION("Linux Kaleidoscope: Chapter 4, Question 12");
MODULE_LICENSE("GPL v2");

static int __init datetime_init(void)
{
    ktime_t time;
    struct tm tm;

    time = ktime_get_real();
    pr_info("%lld", time);

    time64_to_tm(time, 0, &tm);
    pr_info("Second: %d\n", tm.tm_sec);
    pr_info("Minute: %d\n", tm.tm_min);
    pr_info("Hour: %d\n", tm.tm_hour);
    pr_info("Day of month: %d\n", tm.tm_mday);
    pr_info("Month: %d\n", tm.tm_mon);
    pr_info("Year: %ld\n", tm.tm_year);
    pr_info("Weekday: %d\n", tm.tm_wday);
    pr_info("Yearday: %d\n", tm.tm_yday);
    return 0;
}

static void __exit datetime_exit(void)
{
    pr_info("Exiting module...\n");
}

module_init(datetime_init);
module_exit(datetime_exit);