/* 
 *  * procfs1.c 
 *   */ 

#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/proc_fs.h> 
#include <linux/uaccess.h> 
#include <linux/version.h> 

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0) 
#define HAVE_PROC_OPS 
#endif 

#define procfs_name "helloworld" 

static struct proc_dir_entry *our_proc_file; 

static ssize_t procfile_read(struct file *file_pointer, char __user *buffer, 
        size_t buffer_length, loff_t *offset) 
{ 
    char s[200]={0}; 
    int len; 
    ssize_t ret; 

    snprintf(s,sizeof(s), "%s;V:%d;buf_len:%zu;offset:%08lld", "HelloWorld!", LINUX_VERSION_CODE, 
							buffer_length, *offset); 
    len = strlen(s);
    ret = len;

    if (*offset >= len || copy_to_user(buffer, s, len)) { 
        pr_info("copy_to_user failed len:%d;o:%lld.\n",len, *offset); 
        ret = 0; 
    } else { 
        pr_info("procfile read %s;len:%d;o:%lld\n", file_pointer->f_path.dentry->d_name.name,
				len, *offset); 
        *offset += len; 
    } 

    return ret; 
} 

#ifdef HAVE_PROC_OPS 
static const struct proc_ops proc_file_fops = { 
    .proc_read = procfile_read, 
}; 
#else 
static const struct file_operations proc_file_fops = { 
    .read = procfile_read, 
}; 
#endif 

static int __init procfs1_init(void) 
{ 
    our_proc_file = proc_create(procfs_name, 0644, NULL, &proc_file_fops); 
    if (NULL == our_proc_file) { 
        proc_remove(our_proc_file); 
        pr_alert("Error:Could not initialize /proc/%s\n", procfs_name); 
        return -ENOMEM; 
    } 

    pr_info("/proc/%s created\n", procfs_name); 
    return 0; 
} 

static void __exit procfs1_exit(void) 
{ 
    proc_remove(our_proc_file); 
    pr_info("/proc/%s removed\n", procfs_name); 
} 

module_init(procfs1_init); 
module_exit(procfs1_exit); 

MODULE_LICENSE("GPL");
