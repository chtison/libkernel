obj-m += ex07.o
KDIR  := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

insmod:
	insmod ex07.ko

lsmod:
	lsmod | grep ex07 || true

rmmod:
	rmmod ex07

test:
	ls -la /sys/kernel/debug/fortytwo/ && echo OK || echo KO
