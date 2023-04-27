MODULE_NAME := f75111_gpio
KERNEL_MODULE := $(MODULE_NAME).ko

obj-m := $(MODULE_NAME).o

INSTALL_MOD_PATH ?= $(DESTDIR)
export INSTALL_MOD_PATH

INSTALL_MOD_DIR ?= "extra"
export INSTALL_MOD_DIR

KDIR ?= /lib/modules/$(shell uname -r)/build
KERNELPATH := $(shell realpath $(KDIR)/..)/kernel/drivers/innomotics

LINUXINCLUDE := -I$(PWD)/include/ $(LINUXINCLUDE)

modules modules_install clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $@

sign: modules
	$(KDIR)/scripts/sign-file sha512 ../temp/.priv ../temp/.x509 $(KERNEL_MODULE)
	zstd $(KERNEL_MODULE)
