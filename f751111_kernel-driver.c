/*
 * Innomotics LED driver for IPCs using F75111
 *
 * Copyright (c) Siemens AG, 2018-2023
 *
 * Authors:
 *  Mathias Haimerl <mathias.haimerl@siemens.com>
 * Based on Code by:
 *  Henning Schild <henning.schild@siemens.com>
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *  Gerd Haeussler <gerd.haeussler.ext@siemens.com>
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/dmi.h>
#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/leds.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/sizes.h>
#include <linux/spinlock.h>
#include <linux/string.h>

#include <linux/version.h>
#if KERNEL_VERSION(4, 11, 0) > LINUX_VERSION_CODE
#define LED_ON				1
#endif
#if KERNEL_VERSION(5, 4, 0) > LINUX_VERSION_CODE
#define LED_FUNCTION_STATUS "status"
#define LED_FUNCTION_DISK_ERR "disk-err"
#define LED_FUNCTION_ALARM "alarm"
#endif

//#include "libF75111.h"
#include "innomotics.h"

/**
 * led_color defines the F75111 pin offset from the LED base
 */

static struct i2c_client *i2c_cli;
static struct platform_device *pdev;
static unsigned long flags;

static DEFINE_SPINLOCK(reg_lock);

void set_digital_output(u8 data) {
    pr_info("Sending SMBus: %x", data);
    //spin_lock_irqsave(&reg_lock, flags);
    i2c_smbus_write_byte(i2c_cli, data);
    //spin_unlock_irqrestore(&reg_lock, flags);
}

bool set_output_pin(u8 pin_number, bool pin_status)
{
    u8 a = 0x1;
    u8 byteData = 0;
    s32 byteIn1 = 0;
    s32 byteIn2 = 0;

    //spin_lock_irqsave(&reg_lock, flags);
    byteIn1 = i2c_smbus_read_byte(i2c_cli);
    //spin_unlock_irqrestore(&reg_lock, flags);

    printk("Read data from SMBus: %x", byteIn1);

    if((pin_number >= 0 ) && (pin_number <= 7))
    {
        byteData = (byteIn1 & 0x01 )? byteData + 0x01 : byteData;
        byteData = (byteIn1 & 0x02 )? byteData + 0x02 : byteData;
        byteData = (byteIn1 & 0x04 )? byteData + 0x04 : byteData;
        byteData = (byteIn1 & 0x80 )? byteData + 0x08 : byteData;

        byteData = (byteIn1 & 0x40 )? byteData + 0x10 : byteData;
        byteData = (byteIn1 & 0x20 )? byteData + 0x20 : byteData;
        byteData = (byteIn1 & 0x10 )? byteData + 0x40 : byteData;
        byteData = (byteIn1 & 0x08 )? byteData + 0x80 : byteData;
    }
    else if ((pin_number >= 8 ) && (pin_number <= 15))
    {
        //spin_lock_irqsave(&reg_lock, flags);
        byteIn2 = i2c_smbus_read_byte(i2c_cli);
        //spin_unlock_irqrestore(&reg_lock, flags);
        printk("Read additional data from SMBus: %x", byteIn2);

        byteData = (byteIn1 & 0x10 )? byteData + 0x01 : byteData;
        byteData = (byteIn1 & 0x80 )? byteData + 0x02 : byteData;
        byteData = (byteIn1 & 0x40 )? byteData + 0x04 : byteData;
        byteData = (byteIn2 & 0x01 )? byteData + 0x08 : byteData;

        byteData = (byteIn2 & 0x02 )? byteData + 0x10 : byteData;
        byteData = (byteIn2 & 0x04 )? byteData + 0x20 : byteData;
        byteData = (byteIn2 & 0x08 )? byteData + 0x40 : byteData;
        byteData = (byteIn1 & 0x20 )? byteData + 0x80 : byteData;
    }
    a = a<< ((pin_number-1)%8);
    if(pin_status)
        set_digital_output(byteData | a);
    else
        set_digital_output(byteData & ~a);
    return true;
}

static inline struct innomotics_ipc_led *cdev_to_led(struct led_classdev *led_cd)
{
	return container_of(led_cd, struct innomotics_ipc_led, cdev);
}

static void set_led(u16 ledNum, enum led_color col, bool on) {
    printk("Setting LED #%d %s to %d\n", ledNum, colors[col], on);

	innomotics_ipc_led *ipcled ;
    ipcled = innomotics_ipc_leds_f75111;

	while (ipcled->num) {
        if (ipcled->num == ledNum && ipcled->color == col) {
            printk("Setting pin %d\n", ipcled->pin);
            set_output_pin(ipcled->pin, on);
            break;
        }
		ipcled++;
	}
}

static enum led_brightness innomotics_ipc_led_get_io(struct led_classdev *led_cd)
{
    struct innomotics_ipc_led *led = cdev_to_led(led_cd);

    // FIXME: How?
    return 0;
}

static void innomotics_ipc_led_set_io(struct led_classdev *led_cd, enum led_brightness brightness)
{
	struct innomotics_ipc_led *led = cdev_to_led(led_cd);
    set_led(led->num, led->color, brightness);
}

static void pr_i2c_adap(struct i2c_adap *adapter) {
    pr_info("%pTN<struct i2c_adapter>", adapter);
}

static int f75111n_ipc_leds_probe(struct platform_device *pdev)
{
    int err;
    struct device *dev = &pdev->dev;
    struct led_classdev *cdev;
    struct innomotics_ipc_led *ipcled = innomotics_ipc_leds_f75111;

    struct i2c_adapter *i2c_adap;

    int i;
    for (i = 0; i < 12; i++) {
        i2c_adap = i2c_get_adapter(i);
        if (strstr(i2c_adap->name, "SMBus")) {
            printk("Using I2C Adapter #%d: %x: %s\n", i2c_adap->nr, (int) i2c_adap, i2c_adap->name);
            break;
        }
    }

    i2c_cli = i2c_new_client_device(i2c_adap, &i2c_info);
    pr_info("%pTN<struct i2c_client>", i2c_cli);

    printk("Innomotics kernel module started; I2C Address: %x\n", i2c_cli);

	while (ipcled->num) {
		cdev = &ipcled->cdev;
        cdev->brightness_set = innomotics_ipc_led_set_io;
        cdev->brightness_get = innomotics_ipc_led_get_io;
		cdev->max_brightness = LED_ON;
		cdev->name = ipcled->name;

		err = devm_led_classdev_register(dev, cdev);
		if (err < 0) {
			cleanup_module();
			return err;
		}
		ipcled++;
	}
    printk("Loaded Innomotics LED kernel module\n");
	return 0;
}
/*

static int f75111n_ipc_leds_probe(struct platform_device *pdev)
{
    struct i2c_adapter *i2c_adap;
    struct i2c_board_info i2c_info;
    struct i2c_client *f75111_i2c_client;

    i2c_adap = i2c_get_adapter(0);
    memset(&i2c_info, 0, sizeof(struct i2c_board_info));
    strscpy(i2c_info.type, "f75111", sizeof(i2c_info.type));
    f75111_i2c_client = i2c_new_scanned_device(i2c_adap, &i2c_info, normal_i2c, NULL);

    int err;
	struct device *dev = &pdev->dev;
	struct led_classdev *cdev;
	struct innomotics_ipc_led *ipcled = innomotics_ipc_leds_f75111;

    printk("Innomotics kernel module started\n");

	while (ipcled->num) {
		cdev = &ipcled->cdev;
        cdev->brightness_set = innomotics_ipc_led_set_io;
        cdev->brightness_get = innomotics_ipc_led_get_io;
		cdev->max_brightness = LED_ON;
		cdev->name = ipcled->name;

		err = devm_led_classdev_register(dev, cdev);
		if (err < 0) {
			cleanup_module();
			return err;
		}
		ipcled++;
	}
    printk("Loaded Innomotics LED kernel module\n");
	return 0;
}
 */

static struct platform_driver innomotics_ipc_led_driver = {
	.probe = f75111n_ipc_leds_probe,
//    .id_table = innomotics_idtable,
	.driver = {
		.name = KBUILD_MODNAME,
	},
};

static int __init wrap_led_init(void)
{
    int ret;
    ret = platform_driver_register(&innomotics_ipc_led_driver);
    if (ret < 0) return ret;

    pdev = platform_device_register_simple(KBUILD_MODNAME, -1, NULL, 0);
    if (IS_ERR(pdev)) {
        ret = PTR_ERR(pdev);
        platform_driver_unregister(&innomotics_ipc_led_driver);
        return ret;
    }
    return ret;
}

static void __exit wrap_led_exit(void)
{
    platform_driver_unregister(&innomotics_ipc_led_driver);
}

module_init(wrap_led_init);
module_exit(wrap_led_exit);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" KBUILD_MODNAME);
MODULE_AUTHOR("Mathias Haimerl <mathias.haimerl@siemens.com>");
