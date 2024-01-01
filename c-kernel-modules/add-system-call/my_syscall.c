#include <linux/kernel.h>
#include <linux/syscalls.h>

asmlinkage long sys_my_syscall(void)
{
    printk(KERN_INFO "My system call!\n");
    return 0;
}

static const struct syscall_metadata my_syscall_metadata = {
    .name = "my_syscall",
    .nb_args = 0,
};

static const struct syscall_table my_syscall_table = {
    .nr = 333,
    .metadata = &my_syscall_metadata,
};

static int __init my_syscall_init(void)
{
    int ret;

    ret = syscall_register_table(&my_syscall_table);
    if (ret)
        printk(KERN_ERR "Failed to register my system call!\n");

    return ret;
}

static void __exit my_syscall_exit(void)
{
    syscall_unregister_table(&my_syscall_table);
}

module_init(int, my_syscall_init);
module_exit(my_syscall_exit);
MODULE_LICENSE("GPL");

