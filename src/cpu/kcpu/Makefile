# Makfile for kcpu

TARGET = kcpu

obj-m := $(TARGET).o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.cmd
	rm -rf modules.order
	rm -rf Module.symvers
	rm -rf *.o
	rm -rf *.mod.c
	rm -rf .*.ko.cmd
	rm -rf .*.o.cmd
	rm -rf .*.o.d
	rm -rf *.ko
	rm -rf .tmp_versions

