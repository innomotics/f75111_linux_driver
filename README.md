# Innomotics Linux LED Driver

[![License](https://img.shields.io/badge/License-GPLv2-green.svg)](https://opensource.org/license/gpl-2-0/)

The _SIDRIVEIQ NextGenNano_ (hereinafter NGN) platform developed by [Lex System](https://www.lex.com.tw/en/) provided
no driver for the _F75111_ (GPIO over SMBUS) chip.

We created a driver as a [Linux Kernel Module](https://sysprog21.github.io/lkmpg/#what-is-a-kernel-module), based off
the documentation and source-code for the "driverless" LED-application provided from _Lex System_.

## Hardware Considerations and Starting Points

The NGN is based on the [Intel Elkhart Lake](https://www.intel.com/content/www/us/en/products/platforms/details/elkhart-lake.html)
infrastructure and thus providing an [SMBus](https://www.nxp.com/docs/en/application-note/AN4471.pdf)
using the linux standard [`i2c_i801`](https://www.kernel.org/doc/html/latest/i2c/busses/i2c-i801.html) kernel module.

_Lex System_ provides LED access using a basic [GPIO](https://en.wikipedia.org/wiki/General-purpose_input/output) protocol.
To provide a dedicated chip for GPIO purposes, a [Fintek F75111](https://www.fintek.com.tw/index.php/led-driver-ic/item/10-f75111) silicon was used.
The _F75111_ is connected to the system to the _SMBus_.

> The official SMBus address of the _F75111_ silicon is the 8 Bit address `0x9c`.<br />
> As SMBus addressing is requiring [7 Bit addresses](https://www.totalphase.com/support/articles/200349176-7-bit-8-bit-and-10-bit-I2C-Slave-Addressing/), the address needed to be adjusted.<br />
> We found experimentally, that the address is __shifted right 1 Bit__ to `0x4e`.

The implementation from _Lex System_ is accessing the device using shared memory with the starting address 
of the _F75111_ address and accessing values over high-level APIs while accessing low-level IO functionalities 
instead of the high-level SMBus functions.

## Creation of the Kernel Module
We started with a very basic kernel module following the [Linux Kernel Modules Documentation](https://docs.kernel.org/i2c/index.html).

The basic kernel functionality is as follows:

1. Initialization
    * Register driver module in the kernel
    * Probe for the _F75111_ silicon
      * Find the `I801` I2C adapter
      * Open I2C client at address `0x9c >> 1 = 0x4e`
      * For each defined LED (1-red, 1-orange, 1-green, 2-red, 2-orange, 2-green)
        * Register system device of LED class type
2. Operation
    * (a) Set brightness
      * Get LED configuration matching the requested device
      * Request the current value from the GPIO _read_ register
      * Set (`brightness=1`) or unset (`brightness=0`) the LED color's bit
      * Write the new value to the GPIO _write_ register
    * (b) Get brightness
      * Get LED configuration matching the requested device
      * Request the current value from the GPIO _read_ register
      * Test if the LED color's bit is set (`brightness=1`) or unset (`brightness=0`)
3. Shutdown
   * Unregister I2C client
   * Unregister `I801` I2C adapter
   * Unregister kernel driver

## Detail infos

The reverse engineering led to many unnecessary functionality in the User-space implementation.
This is the condensed version for all necessary functionality.

Also, the register `F75111_CONFIGURATION` (`0x03`) is set to `0x03` at the start.

### GPIO Configuration

The _LED 1_ is available via 2X GPIOs, _LED 2_ via 1X GPIOs: 

| LED   | Constant              | Address |
|-------|-----------------------|---------|
| LED 1 | GPIO2X_CONTROL_MODE   | 0x20    |
| LED 1 | GPIO2X_OUTPUT_DATA    | 0x21    |
| LED 1 | GPIO2X_INPUT_DATA     | 0x22    |
| LED 1 | GPIO2X_OUTPUT_DRIVING | 0x2B    |
| LED 2 | GPIO1X_CONTROL_MODE   | 0x10    |
| LED 2 | GPIO1X_OUTPUT_DATA    | 0x11    |
| LED 2 | GPIO1X_INPUT_DATA     | 0x12    |
| LED 2 | GPIO1X_OUTPUT_DRIVING | 0x1B    |

Also, the color coding bits differ from LED to LED

| LED   | Color                 | Bit  |
|-------|-----------------------|------|
| LED 1 | Red                   | 0x01 |
| LED 1 | Orange                | 0x02 |
| LED 1 | Green                 | 0x04 |
| LED 2 | Red                   | 0x10 |
| LED 2 | Orange                | 0x80 |
| LED 2 | Green                 | 0x40 |

The `GPIOYX_CONTROL_MODE` and `GPIOYX_OUTPUT_DRIVING` registers must be set to `0xFF` to enable output driving.
This is implemented in the `initialize_f75111` function. 