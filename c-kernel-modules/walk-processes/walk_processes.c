// walk_processes.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>  // for_each_process()
#include <linux/sched.h>         // task_struct

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("Walk the process list in a kernel module");

static int __init walk_processes_init(void)
{
    struct task_struct *task;

    printk(KERN_INFO "Process list walker loaded.\n");

    for_each_process(task) {
        printk(KERN_INFO "PID: %d | Name: %s | State: %ld\n",
               task->pid, task->comm, task->state);
    }

    return 0;
}

static void __exit walk_processes_exit(void)
{
    printk(KERN_INFO "Process list walker unloaded.\n");
}

module_init(walk_processes_init);
module_exit(walk_processes_exit);

