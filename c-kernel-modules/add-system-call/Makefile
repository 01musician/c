#it seems impossible to add a new system call to linux as a loadable module.
obj-m += my_syscall.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

