obj-m += helloworld.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:
	insmod helloworld.ko

lsmod:
	lsmod | grep helloworld

rmmod:
	rmmod helloworld
