obj-m += ex09.o
KDIR  := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

insmod:
	insmod ex09.ko

lsmod:
	lsmod | grep ex09 || true

rmmod:
	rmmod ex09
