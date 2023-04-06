obj-m := f751111_kernel-driver.o

INSTALL_MOD_PATH ?= $(DESTDIR)
export INSTALL_MOD_PATH

INSTALL_MOD_DIR ?= "extra"
export INSTALL_MOD_DIR

KDIR ?= /lib/modules/$(shell uname -r)/build

LINUXINCLUDE := -I$(PWD)/include/ $(LINUXINCLUDE)

modules modules_install clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $@
