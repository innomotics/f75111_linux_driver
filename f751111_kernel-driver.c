/*
 * Innomotics LED driver for IPCs using F75111
 *
 * Copyright (c) Innomotics GmbH, 2023
 *
 * Authors:
 *  Mathias Haimerl <mathias.haimerl@siemens.com>
 */
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

#include "innomotics.h"

/**
 * led_color defines the F75111 pin offset from the LED base
 */

static struct i2c_client *i2c_cli;
static struct platform_device *pdev;

/**
 * Write to a SMBus register
 * @param cmd the register/command address
 * @param value the value to write to the register
 */
void smbus_write(u8 cmd, u8 data) {
    i2c_smbus_write_byte_data(i2c_cli, cmd, data);
}

/**
 * Read the current value from a SMBus register
 * @param cmd the register/command address
 * @return the value at the register
 */
u8 smbus_read(u8 cmd) {
    return i2c_smbus_read_byte_data(i2c_cli, cmd);
}

/**
 * Verifies the vendor and device ID to match the F75111
 * @return bool if the queried chip is a F75111
 */
bool verify_f75111() {
    return (
            ((WORD)smbus_read(F75111_VENDOR_ID_REGISTER_2)) << 8 |
            smbus_read(F75111_VENDOR_ID_REGISTER_1)
        ) == F75111_VENDOR_ID
        &&
        (
            ((WORD)smbus_read(F75111_CHIP_ID_REGISTER_2)) << 8 |
            smbus_read(F75111_CHIP_ID_REGISTER_1)
        ) == F75111_DEVICE_ID;
}

/**
 * Initialize the F75111 output GPIOs
 */
void initialize_f75111() {
    if (verify_f75111()) {
        smbus_write(GPIO1X_CONTROL_MODE, 0xFF);
        smbus_write(GPIO1X_OUTPUT_DRIVING, 0xFF);
        smbus_write(GPIO1X_OUTPUT_DATA, 0x00);
        smbus_write(GPIO2X_CONTROL_MODE, 0xFF);
        smbus_write(GPIO2X_OUTPUT_DRIVING, 0xFF);
        smbus_write(GPIO2X_OUTPUT_DATA, 0x00);
        smbus_write(F75111_CONFIGURATION,0x03);
    }
}

/**
 * Set an LED color on or off
 * @param led the led structure
 * @param pin_status boolean indicating the status is on or off
 */
void set_led(innomotics_ipc_led *led, bool pin_status)
{
    u8 byteData;
    if (!led) return;
    byteData = smbus_read(led->pin + 1); // Read register is write register + 1
    if(pin_status)
        byteData |= led->value;
    else
        byteData &= ~led->value;
    smbus_write(led->pin, byteData);
}

/**
 * Get the led structure from the device structure
 * @param led_cd structure of a led class device
 * @return
 */
static inline struct innomotics_ipc_led *cdev_to_led(struct led_classdev *led_cd) {
	return container_of(led_cd, struct innomotics_ipc_led, cdev);
}

/**
 * Get the current brightness of a specific LED
 * Called from LED device base driver
 * @param led_cd structure of a led class device
 * @return enum led_brightness describing if LED is on or off
 */
static enum led_brightness innomotics_ipc_led_get_io(struct led_classdev *led_cd)
{
    struct innomotics_ipc_led *led = cdev_to_led(led_cd);
    return smbus_read(led->pin + 1) & led->value; // Read register is write register + 1
}

/**
 * Set the current brightness of a specific LED
 * Called from LED device base driver
 * @param led_cd structure of a led class device
 * @param enum led_brightness describing if LED is on or off
 */
static void innomotics_ipc_led_set_io(struct led_classdev *led_cd, enum led_brightness brightness)
{
    set_led(cdev_to_led(led_cd), brightness);
}

/**
 * Probe function to find and configure the F75111
 * @param pdev structure of the platform device hardware
 * @return error code or zero
 */
static int f75111n_ipc_leds_probe(struct platform_device *pdev)
{
    int err, i;
    struct i2c_adapter *i2c_adap;
    struct led_classdev *cdev;
    struct innomotics_ipc_led *ipcled;

    // Scan for I2C master adapters
    for (i = 0; i < I2C_MAX_SCAN_ADAPTERS; i++) {
        i2c_adap = i2c_get_adapter(i);
        if (!i2c_adap) return -ENODEV;
        if (strstr(i2c_adap->name, SMBUS_ADAPTER_NEEDLE)) break;
    }
    if (!i2c_adap) return -ENODEV;

    // Create the client device
    i2c_cli = i2c_new_client_device(i2c_adap, &i2c_info);
    if (IS_ERR(i2c_cli))
        return PTR_ERR(i2c_cli);

    // Iterate LEDs and register class devices
    ipcled = innomotics_ipc_leds_f75111;
	while (ipcled->num) {
		cdev = &ipcled->cdev;
        cdev->brightness_set = innomotics_ipc_led_set_io;
        cdev->brightness_get = innomotics_ipc_led_get_io;
		cdev->max_brightness = LED_ON;
		cdev->name = ipcled->name;

		err = devm_led_classdev_register(&pdev->dev, cdev);
		if (err < 0) {
			return err;
		}
		ipcled++;
	}
    initialize_f75111();
    printk(KBUILD_MODNAME " kernel module loaded.\n");
	return 0;
}

/**
 * Define the Innomotics platform driver
 */
static struct platform_driver innomotics_ipc_led_driver = {
	.probe = f75111n_ipc_leds_probe,
	.driver = {
		.name = KBUILD_MODNAME,
	},
};

/**
 * Initializer function for the kernel module
 */
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

/**
 * Exit function for the kernel module
 */
static void __exit wrap_led_exit(void)
{
    i2c_unregister_device(i2c_cli);
    platform_device_unregister(pdev);
    platform_driver_unregister(&innomotics_ipc_led_driver);
}

module_init(wrap_led_init);
module_exit(wrap_led_exit);

MODULE_SOFTDEP("pre: i2c_i801");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" KBUILD_MODNAME);
MODULE_AUTHOR("Mathias Haimerl <mathias.haimerl@siemens.com>");
