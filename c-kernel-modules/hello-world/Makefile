obj-m += hello-1.o 
obj-m += hello-2.o 
<<<<<<< HEAD
=======
obj-m += hello-3.o 
obj-m += hello-4.o 
>>>>>>> aba0db90bd8721a6d962e8e91c35e6ea9847a00a
 
PWD := $(CURDIR) 
 
all: 
	    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
		 
clean: 
	    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
