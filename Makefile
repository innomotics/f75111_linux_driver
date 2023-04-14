obj-m := f75111_gpio.o

KERNEL_MODULE := f75111_gpio.ko

INSTALL_MOD_PATH ?= $(DESTDIR)
export INSTALL_MOD_PATH

INSTALL_MOD_DIR ?= "extra"
export INSTALL_MOD_DIR

KDIR ?= /lib/modules/$(shell uname -r)/build

LINUXINCLUDE := -I$(PWD)/include/ $(LINUXINCLUDE)

modules modules_install clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $@

sign: modules
	$(KDIR)/scripts/sign-file sha512 temp/.priv temp/.x509 $(KERNEL_MODULE)
	zstd $(KERNEL_MODULE)
