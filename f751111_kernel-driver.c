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

#include <linux/delay.h>
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

BYTE i2c_read(BYTE cmd) {
    BYTE result;
    //cmd += F75111_INTERNAL_ADDR;
    result = i2c_smbus_read_byte_data(i2c_cli, cmd);
    printk("[SMBus Info] Reading = %x from address %x\n", result, cmd);
    return result;
}
void i2c_write(BYTE cmd, BYTE data) {
    //cmd += F75111_INTERNAL_ADDR;
    printk("[SMBus Info] Writing = %x to address %x\n", data, cmd);
    i2c_smbus_write_byte_data(i2c_cli, cmd, data);
}

void smbus_clear() {
    i2c_write(0x0,  0xFF);
    udelay(1);
    while (i2c_read(0x0) & 0x01) udelay(1);
    i2c_write(SMBHSTDAT0,  0xFF);
}

int smbus_wait() {
    int	timeout = SMBUS_TIMEOUT;
    BYTE value;

    while(timeout--) {
        // I/O Delay
        udelay(1);
        // Read Host Status Register
        value = i2c_read(0x0);
        if(value & SMBHSTSTS_INTR) return SMBUS_OK;
        if(value &= (SMBHSTSTS_FAILED | SMBHSTSTS_COLLISION | SMBHSTSTS_ERROR)) return value;
    }
    return SMBUS_BUSY;
}

bool smbus_busy() {
    return i2c_read(0x0) & SMBHSTSTS_BUSY;
}

void smbus_write(BYTE cmd, BYTE value) {
    printk("Send byte '%x' to SMBus function %x\n", value, cmd);
    smbus_clear();
    if (!smbus_busy()) {
        i2c_write(cmd, value);
        smbus_wait();
    }
}

BYTE smbus_read(BYTE cmd) {
    smbus_clear();
    if (!smbus_busy()) {
        i2c_write(SMBHSTADD, F75111_INTERNAL_ADDR | 0x01);
        i2c_write(SMBHSTCMD, cmd);
        i2c_write(SMBHSTCNT, SMBHSTCNT_BYTE | SMBHSTCNT_START);
    }
    if (smbus_wait() == SMBUS_OK) {
        return i2c_read(SMBHSTDAT0);
    }
    return 0x0;
}

bool is_chip(WORD deviceID, BYTE chipReg2, BYTE chipReg1)
{
    return (smbus_read(chipReg2) << 8 | smbus_read(chipReg1)) == deviceID;
}

void initialize_f75111() {
    char tmp;
    BYTE byteGPIO1X;

    // Initialize SMBus
    //tmp = i2c_read(SMBAUXCTL);
    //printk("Read SMBAUXCTL from SMBus: %x", tmp);
    //i2c_write(SMBAUXCTL, tmp & ~(SMBAUXCTL_CRC | SMBAUXCTL_E32B));

    printk("is_chip result: %x", is_chip(F75111_DEVICE_ID, F75111_CHIP_ID_REGISTER_2, F75111_CHIP_ID_REGISTER_1));
    // Initialize F75111
    if (is_chip(F75111_DEVICE_ID, F75111_CHIP_ID_REGISTER_2, F75111_CHIP_ID_REGISTER_1)) {
        byteGPIO1X = smbus_read(GPIO1X_OUTPUT_DATA);
        smbus_write(GPIO1X_CONTROL_MODE, (byteGPIO1X & 0x0f) | 0xf0);
        smbus_write(GPIO1X_OUTPUT_DRIVING, (byteGPIO1X & 0x0f) | 0xf0);
        smbus_write(GPIO2X_CONTROL_MODE, 0xFF);
        smbus_write(GPIO2X_OUTPUT_DRIVING, 0xFF);
        smbus_write(GPIO3X_CONTROL_MODE, 0x0F);
        smbus_write(GPIO3X_OUTPUT_DRIVING, 0x0F);
        smbus_write(F75111_CONFIGURATION,0x03);
        smbus_write(0x06, 0x04);
    }
}

void set_output_pin(u8 pin_number, bool pin_status)
{
    u8 a;
    u8 byteData = 0;
    s32 byteIn1 = 0;
    s32 byteIn2 = 0;

    byteIn1 = smbus_read(GPIO2X_INPUT_DATA);
    printk("Read data from SMBus: %x", byteIn1);

    if((pin_number >= 0 ) && (pin_number <= 7))
    {
        a = 0x1 << (pin_number-1);
        byteData = (byteIn1 & 0x01 )? byteData + 0x01 : byteData;
        byteData = (byteIn1 & 0x02 )? byteData + 0x02 : byteData;
        byteData = (byteIn1 & 0x04 )? byteData + 0x04 : byteData;
        byteData = (byteIn1 & 0x80 )? byteData + 0x08 : byteData;

        byteData = (byteIn1 & 0x40 )? byteData + 0x10 : byteData;
        byteData = (byteIn1 & 0x20 )? byteData + 0x20 : byteData;
        byteData = (byteIn1 & 0x10 )? byteData + 0x40 : byteData;
        byteData = (byteIn1 & 0x08 )? byteData + 0x80 : byteData;

        if(pin_status)
            byteData |= a;
        else
            byteData &= ~a;
        smbus_write(GPIO2X_OUTPUT_DATA, byteData);
    }
    else if ((pin_number >= 8 ) && (pin_number <= 15))
    {
        a = 0x1 << ((pin_number-1)%8);
        byteIn2 = smbus_read(GPIO2X_INPUT_DATA);
        printk("Read additional data from SMBus: %x", byteIn2);

        byteData = (byteIn1 & 0x10 )? byteData + 0x01 : byteData;
        byteData = (byteIn1 & 0x80 )? byteData + 0x02 : byteData;
        byteData = (byteIn1 & 0x40 )? byteData + 0x04 : byteData;
        byteData = (byteIn2 & 0x01 )? byteData + 0x08 : byteData;

        byteData = (byteIn2 & 0x02 )? byteData + 0x10 : byteData;
        byteData = (byteIn2 & 0x04 )? byteData + 0x20 : byteData;
        byteData = (byteIn2 & 0x08 )? byteData + 0x40 : byteData;
        byteData = (byteIn1 & 0x20 )? byteData + 0x80 : byteData;

        if(pin_status)
            byteData |= a;
        else
            byteData &= ~a;
        smbus_write(GPIO1X_OUTPUT_DATA, byteData);
        smbus_write(GPIO3X_OUTPUT_DATA, byteData);
    }
}

static inline struct innomotics_ipc_led *cdev_to_led(struct led_classdev *led_cd)
{
	return container_of(led_cd, struct innomotics_ipc_led, cdev);
}

static void set_led(u16 ledNum, enum led_color col, bool on) {
	innomotics_ipc_led *ipcled ;
    ipcled = innomotics_ipc_leds_f75111;

    printk("Setting LED #%d %s to %d\n", ledNum, colors[col], on);
	while (ipcled->num) {
        if (ipcled->num == ledNum && ipcled->color == col) {
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
        if (strstr(i2c_adap->name, "SMBus")) break;
    }

    i2c_cli = i2c_new_client_device(i2c_adap, &i2c_info);
    printk("Innomotics kernel module started; I2C Client %s, Address: %x\n", i2c_cli->name, i2c_cli->addr);

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
    printk("Registering F75111 chip...\n");
    initialize_f75111();
    printk("Loaded Innomotics LED kernel module\n");
	return 0;
}

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
    i2c_unregister_device(i2c_cli);
    platform_driver_unregister(&innomotics_ipc_led_driver);
}

module_init(wrap_led_init);
module_exit(wrap_led_exit);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" KBUILD_MODNAME);
MODULE_AUTHOR("Mathias Haimerl <mathias.haimerl@siemens.com>");
