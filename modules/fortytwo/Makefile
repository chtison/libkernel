obj-m += fortytwo.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:
	insmod fortytwo.ko

lsmod:
	lsmod | grep fortytwo || true

rmmod:
	rmmod fortytwo

test:
	[ "`cat /dev/fortytwo`" = "chtison" ] && echo OK || echo KO
	echo chtison > /dev/fortytwo && echo OK || echo KO
