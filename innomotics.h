#ifndef CIO_LED_FLASH_F75111_INNOMOTICS_H
#define CIO_LED_FLASH_F75111_INNOMOTICS_H

#define LED1_PIN_OFFSET 0
#define LED2_PIN_OFFSET 8

#define DMI_ENTRY_OEM		129
#define OEM_TYPE_ID_STATIONID	0x02
#define INVALID_STATION_ID	0
#define OEM_TYPE_ID_PS		0x06
//--------------------------------------------------------------------------------------------------------
#define F75111_INTERNAL_ADDR			0x9C 	//	OnBoard  F75111 Chipset
#define F75111_EXTERNAL_ADDR			0x6E	//	External F75111 Chipset


const struct i2c_board_info i2c_info = {
        I2C_BOARD_INFO("f75111", F75111_EXTERNAL_ADDR),
};
const unsigned short normal_i2c[] = { F75111_INTERNAL_ADDR, F75111_EXTERNAL_ADDR, I2C_CLIENT_END };

const struct dmi_system_id innomotics_ipc_whitelist[] = {
    {
        .matches = {
            DMI_MATCH(DMI_SYS_VENDOR, "SIDRIVEIQ"),
        },
    },
    {}
};

struct innomotics_ipc_platform {
    u8	            devmode;			/* device mode */
    u16		        sio_addr;			/* sio io port address */
    void	        *nvram_dev;			/* nvram pci device address */
    u32		        nvram_did;			/* nvram pci device id */
    struct resource *gpio_base;			/* gpio base address for 2x7d and 4x7d */
};

struct find_dmi_data {
	u8	type;
	u32	station_id;
	u8	ps_type;
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
    char name[32];
    struct led_classdev cdev;
} innomotics_ipc_led;

struct innomotics_ipc_led innomotics_ipc_leds_f75111[] = {
        {1, RED, LED1_PIN_OFFSET + RED, "red:" LED_FUNCTION_STATUS "-1"},
        {1, ORANGE, LED1_PIN_OFFSET + ORANGE, "orange:" LED_FUNCTION_STATUS "-1"},
        {1, GREEN, LED1_PIN_OFFSET + GREEN,  "green:" LED_FUNCTION_STATUS "-1"},
        {2, RED, LED2_PIN_OFFSET + RED, "red:" LED_FUNCTION_STATUS "-2"},
        {2, ORANGE, LED2_PIN_OFFSET + ORANGE, "orange:" LED_FUNCTION_STATUS "-2"},
        {2, GREEN, LED2_PIN_OFFSET + GREEN, "green:" LED_FUNCTION_STATUS "-2"},
        {0, 0, 0, ""},
};
char* colors[] = {"", "RED", "ORANGE", "GREEN"};


#endif
