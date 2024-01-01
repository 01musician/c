CentOS 7虚拟机，grub add new entry:

环境说明：
gcc --version
gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)

[root@node01 ~]# cat /etc/redhat-release
CentOS Linux release 7.6.1810 (Core)


下面是添加HelloOS启动项的流程：

1.在/etc/grub.d/40_custom文件中，添加HelloOS在grub2中的配置
#!/bin/sh
exec tail -n +3 $0
# This file provides an easy way to add custom menu entries.  Simply type the
# menu entries you want to add after this comment.  Be careful not to change
# the 'exec tail' line above.

#以下是添加内容

menuentry 'HelloOS' {

        insmod part_msdos #GRUB加载分区模块识别分区
        insmod ext2 #GRUB加载ext文件系统模块识别ext文件系统
        set root='hd0,msdos1' #注意boot目录挂载的分区，这是我机器上的情况
        multiboot2 /HelloOS.bin #GRUB以multiboot2协议加载HelloOS.bin
        boot #GRUB启动HelloOS.bin
}



2.重新生成/boot/grub2/grub.cfg文件
[root@node01 grub2]# grub2-mkconfig -o /boot/grub2/grub.cfg

3.重启VM，即可在grub引导项中看到多了HelloOS

