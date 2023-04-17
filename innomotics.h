#ifndef CIO_LED_FLASH_F75111_INNOMOTICS_H
#define CIO_LED_FLASH_F75111_INNOMOTICS_H

#define SMBUS_ADAPTER_NEEDLE "SMBus I801"

//----------------------------------------------------------------------------------
// The F75111 addresses are defined in 8-Bit format. For I2C-addressing,
// they must be shifted right 1 bit!
#define F75111_INTERNAL_ADDR	0x9C 	//	OnBoard  F75111 Chipset
#define F75111_EXTERNAL_ADDR	0x6E	//	External F75111 Chipset
//----------------------------------------------------------------------------------
//	F75111 Chip Vendor id / Chip ID
//----------------------------------------------------------------------------------
#define F75111_CHIP_ID_REGISTER_1				0x5A
#define F75111_CHIP_ID_REGISTER_2				0x5B
#define F75111_DEVICE_ID						0x0003

#define F75111_VENDOR_ID_REGISTER_1				0x5D
#define F75111_VENDOR_ID_REGISTER_2				0x5E
#define F75111_VENDOR_ID						0x3419
//--------------------------------------------------------------------------------------------------------
#define F75111_CONFIGURATION			0x03	//  Configuration and function select Register, Configure GPIO10 to WDTOUT2 Function
//--------------------------------------------------------------------------------------------------------
#define GPIO1X_CONTROL_MODE				0x10	//  Select GPIO1X Output Mode or Input Mode
#define GPIO2X_CONTROL_MODE				0x20	//  Select GPIO2X Output Mode or Input Mode
#define GPIO3X_CONTROL_MODE				0x40	//  Select GPIO3X Output Mode or Input Mode
//--------------------------------------------------------------------------------------------------------
#define GPIO1X_INPUT_DATA				0x12	//  GPIO1X Input
#define GPIO2X_INPUT_DATA				0x22	//  GPIO2X Input 20190828 add by Nico
#define GPIO3X_INPUT_DATA				0x42	//  GPIO3X Input
//--------------------------------------------------------------------------------------------------------
#define GPIO1X_OUTPUT_DATA				0x11    //  GPIO1X Output 20190828 add by Nico
#define GPIO2X_OUTPUT_DATA				0x21	//  GPIO2X Output
#define GPIO3X_OUTPUT_DATA				0x41	//  GPIO3X Output
//--------------------------------------------------------------------------------------------------------
#define GPIO1X_OUTPUT_DRIVING			0x1B	//  Select GPIO1X Output Mode or Input Mode 20190828 add by Nico
#define GPIO2X_OUTPUT_DRIVING			0x2B	//  Select GPIO2X Output Mode or Input Mode
#define GPIO3X_OUTPUT_DRIVING			0x4B	//  Select GPIO4X Output Mode or Input Mode
//--------------------------------------------------------------------------------------------------------
#define GPIO1X_LevelPulse_Control_Register	0x13	//GPIO1X output mode, 0-Level, 1-Pluse Power-on default [7:0] =0000_0000b
#define GPIO2X_LevelPulse_Control_Register	0x23	//GPIO2X output mode, 0-Level, 1-Pluse
#define GPIO3X_LevelPulse_Control_Register	0x43	//GPIO3X output mode, 0-Level, 1-Pluse
//--------------------------------------------------------------------------------------------------------
#define	GPIO1X_Pulse_Width_Control			0x14	//bit 1:0 PLSWD[1:0]
#define	GPIO2X_Pulse_Width_Control			0x24	//00b - 500us
#define	GPIO3X_Pulse_Width_Control			0x44	//01b - 1ms
//--------------------------------------------------------------------------------------------------------
#define I2C_MAX_SCAN_ADAPTERS       16

const struct i2c_board_info i2c_info = {
    // The internal address in Linux I2C is not 8 Bit, but 7 bit.
    // Thus, the 8-Bit Address must be shifted left by 1 bit
    I2C_BOARD_INFO("f75111", F75111_INTERNAL_ADDR >> 1),
};

enum led_color {
    RED = 1,
    ORANGE = 2,
    GREEN = 3,
};

typedef struct innomotics_ipc_led {
    u16 num;
    enum led_color color;
    u16 pin;
    u16 value;
    char name[32];
    struct led_classdev cdev;
} innomotics_ipc_led;

struct innomotics_ipc_led innomotics_ipc_leds_f75111[] = {
        {1, RED,    GPIO2X_OUTPUT_DATA, 0x01, LED_FUNCTION_STATUS "1::red"},
        {1, ORANGE, GPIO2X_OUTPUT_DATA, 0x02, LED_FUNCTION_STATUS "1::orange"},
        {1, GREEN,  GPIO2X_OUTPUT_DATA, 0x04, LED_FUNCTION_STATUS "1::green"},
        {2, RED,    GPIO1X_OUTPUT_DATA, 0x10, LED_FUNCTION_STATUS "2::red"},
        {2, ORANGE, GPIO1X_OUTPUT_DATA, 0x80, LED_FUNCTION_STATUS "2::orange"},
        {2, GREEN,  GPIO1X_OUTPUT_DATA, 0x40, LED_FUNCTION_STATUS "2::green"},
        {0, 0, 0, 0, ""},
};
const char* colors[] = {"", "RED", "ORANGE", "GREEN"};

extern void smbus_write(u8 cmd, u8 value);
extern u8 smbus_read(u8 cmd);
extern bool verify_f75111(void);
extern void initialize_f75111(void);
extern void set_led(innomotics_ipc_led *led, bool pin_status);

#endif
