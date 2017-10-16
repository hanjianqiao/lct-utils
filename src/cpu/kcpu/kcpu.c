#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/slab.h>

static int numOfTasks = 4;
module_param(numOfTasks, int, 0);
MODULE_PARM_DESC(numOfTasks, "Number of Tasks");

static struct task_struct ** kcpu_tasks;

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
    int i;
    kcpu_tasks = (struct task_struct **)kmalloc(sizeof(struct task_struct *) * numOfTasks, GFP_KERNEL);
    for(i = 0; i < numOfTasks; i++){
        kcpu_tasks[i] = kthread_run(kcpu_task_func, NULL, "kcpu_%d", i);
        if (!IS_ERR(kcpu_tasks[i]))
        {
            printk("kthread_create kcpu task %d done\n", i);
        }
        else
        {
            printk("kthread_create kcpu task %d error\n", i);
        }
    }
    return 0;
}

static void __exit kcpu_exit(void)
{
    int i;
    for(i = 0; i < numOfTasks; i++){
        if(kcpu_tasks[i]){
            kthread_stop(kcpu_tasks[i]);
            printk("kcup task %d stopped\n", i);
        }else{
            printk("kcup task %d already stopped\n", i);
        }
    }
    kfree(kcpu_tasks);
}

module_init(kcpu_init);
module_exit(kcpu_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("KCPU Module");
MODULE_AUTHOR("hanjianqiao");
