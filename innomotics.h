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


//----------------------------------------------------------------------------------
// SMBHSTSTS ¹ïÀ³ºXŒÐ
#define SMBHSTSTS_BUSY              0x01        // SMBus Host -> 0000-0001 Busy
#define SMBHSTSTS_INTR              0x02        // SMBus Host -> 0000-0010 Interrupt / complection
#define SMBHSTSTS_ERROR             0x04        // SMBus Host -> 0000-0100 Error        (Device Error)
#define SMBHSTSTS_COLLISION         0x08        // SMBus Host -> 0000-1000 Collistion   (Bus Error)
#define SMBHSTSTS_FAILED            0x10        // SMBus Host -> 0001-0000 Failed
#define SMBHSTSTS_SMBALERT_STS      0x20
#define SMBHSTSTS_INUSE_STS         0x40        // SMBus is in use, can't use it!
#define SMBHSTSTS_BYTE_DONE         0x80
#define STATUS_ERROR_FLAGS          (SMBHSTSTS_ERROR | SMBHSTSTS_COLLISION | SMBHSTSTS_FAILED)
#define STATUS_FLAGS                (SMBHSTSTS_BYTE_DONE | SMBHSTSTS_INTR | STATUS_ERROR_FLAGS)
//----------------------------------------------------------------------------------
// SMBHSTCNT ¹ïÀ³ºXŒÐ
#define SMBHSTCNT_INTREN            0x01        // ŠpªG³]žm¡A«h¯àŠb©R¥O°õŠæ§¹Šš®É²£¥Í€€Â_¡C
#define SMBHSTCNT_KILL              0x02        // ŠpªG³]žm¡A±±šîŸ¹±N€€€î·í«ešÆ°È¡A±NFAILEDª¬ºAŠìžm1¡AšÃŠb€¹³\€€Â_ªº±¡ªp€U²£¥Í€€Â_¡C ³]žm«á¡AžÓŠì¥²¶·¥Ñ³n¥ó²M°£¡A¥H€¹³\±±šîŸ¹¥¿±`¹BŠæ
#define SMBHSTCNT_QUICK             0x00        // Quick Command
#define SMBHSTCNT_SENDRECV          0x04        // Send/Receive Byte
#define SMBHSTCNT_BYTE              0x08        // Write/Read Byte

#define SMBHSTCNT_PROCCALL          0x10        // Process Call
#define SMBHSTCNT_BLOCK             0x14        // Block Write/Read
#define SMBHSTCNT_START             0x40        // SMBus Host Contorl -> 0100 0000 Start
#define SMBHSTCNT_I2C_BLOCK         0x18        // I2C Read                                  (Intel ©M VIA €£€@­P)
#define SMBHSTCNT_BLOCK_PROCCALL    0x1C        // Block Write-Block Read Process Call       (Intel ©M VIA €£€@­P)
#define SMBHSTCNT_LASTBYTE          0x20        // SMBus Host Contorl -> 0010 0000 Last Byte (Intel ©M VIA €£€@­P)(¥Î©ó°Ï¶ôÅªšú)
//----------------------------------------------------------------------------------
// SMBAUXSTS ¹ïÀ³ºXŒÐ
#define SMBAUXSTS_CRCE              0x01
#define SMBAUXSTS_STCO              0x02
//----------------------------------------------------------------------------------
// SMBAUXCTL ¹ïÀ³ºXŒÐ
#define SMBAUXCTL_CRC               0x01
#define SMBAUXCTL_E32B              0x02
//----------------------------------------------------------------------------------
// Intel/VIA SMBus ±±šîŒÈŠsŸ¹
#define SMBHSTSTS                   0x00        // SMBus Host  Status Register Offset
#define SMBHSTCNT                   0x02        // SMBus Host Contorl Register Offset
#define SMBHSTCMD                   0x03        // SMBus Host Command       Register Offset
#define SMBHSTADD                   0x04        // SMBus Host Address       Register Offset
#define SMBHSTDAT0                  0x05        // SMBus Host Data0         Register Offset (Block Counter)
#define SMBHSTDAT1                  0x06        // SMBus Host Data1         Register Offset
#define SMBBLKDAT                   0x07        // SMBus Host Block Data    Register Offset
// Intel Only
#define SMBHSTPEC                   0x08        // Packet Error Check
#define SMBAUXSTS                   0x0C        // SMBus Host Auxiliary Status 8
#define SMBAUXCTL                   0x0D        // SMBus Host Auxiliary Control
#define SMBSLVSTS                   0x10        //
#define SMBSLVCMD                   0x11        //
#define SMBNTFDADD                  0x14        //
#define SMBNTFDDAT                  0x16        //
// VIA only
#define SMBHSLVSTS                  0x01        // SMBus Slave Status Register Offset
#define SMBSLVCNT                   0x08        // SMBus Slave  Control
#define SMBSHDWCMD                  0x09        // SMBus Shadow Command
#define SMBSLVEVT                   0x0a        // SMBus Slave  Event
#define SMBSLVDAT                   0x0c        // SMBus Slave  Data
// SMBus Bus Status Code
#define SMBUS_OK                    0x00        // SMBUS OK
#define SMBUS_BUSY                  0x01        // SMBUS BUSY (¬ÛŠP SMBHSTSTS_BUSY)
#define SMBUS_INT                   0x02        // SMBUS INTR
#define SMBUS_ERROR                 0x04        // SMBUS ERROR
//----------------------------------------------------------------------------------
// Const Data
#define SMBUS_TIMEOUT               100
#define I2C_SMBUS_BLOCK_MAX         32          // SMBus °Ï¶ôŒÒŠ¡³Ì€jŒÆ¶q

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;


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

extern void smbus_clear(void);
extern int smbus_wait(void);
extern bool smbus_busy(void);
extern void smbus_write(BYTE cmd, BYTE value);
extern BYTE smbus_read(BYTE cmd);
extern bool is_chip(WORD deviceID, BYTE chipReg2, BYTE chipReg1);
extern void initialize_f75111(void);
extern void set_output_pin(u8 pin_number, bool pin_status);

#endif
