#include <linux/module.h>
#include <linux/kthread.h>

static struct task_struct * kcpu_task;

static int kcpu_task_func(void *data){
    long long loop = 0, count = 0;

    // be aware of risk of soft lockup
    while(!kthread_should_stop()){
        count++;
        if(count > 1000000000){
            //printk("kcpu_task loop: %d\n", loop++);
            schedule();
        }
    }
    return loop;
}

static int __init kcpu_init(void)
{
    kcpu_task = kthread_run(kcpu_task_func, NULL, "kcpu_task_func");
    if (!IS_ERR(kcpu_task))
    {
        printk("kthread_create rtc_worker done\n");
    }
    else
    {
        printk("kthread_create rtc_worker error\n");
    }
    return 0;
}
 
static void __exit kcpu_exit(void)
{
    if(kcpu_task){
        kthread_stop(kcpu_task);
    }
}
 
module_init(kcpu_init);
module_exit(kcpu_exit);
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("KCPU Module");
MODULE_AUTHOR("hanjianqiao");
