#include<linux/module.h>
#include<linux/time.h>

int init_module(void)
{
    struct tm tm;
    struct timeval tv;
    do_gettimeofday(&tv);
    time_to_tm(tv.tv_sec, +330*60, &tm);
    printk("Second: %d\n", tm.tm_sec);
    printk("Minute: %d\n", tm.tm_min);
    printk("Hour: %d\n", tm.tm_hour);
    printk("Day of month: %d\n", tm.tm_mday);
    printk("Month: %d\n", tm.tm_mon);
    printk("Year: %ld\n", tm.tm_year);
    printk("Weekday: %d\n", tm.tm_wday);
    printk("Yearday: %d\n", tm.tm_yday);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Exiting module...\n"); 
}
