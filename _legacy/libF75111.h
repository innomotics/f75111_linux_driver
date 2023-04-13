#ifndef LIBF75111_H
#define LIBF75111_H

#include <linux/io.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef struct
{
    double t_off;
    double t_on;
    char *color;
    bool flash;
} LED_CONFIG;
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
//10b - 20ms
//11b - 100ms
//--------------------------------------------------------------------------------------------------------
#define WDT_TIMER_RANGE					0x37	//  0-255 (secord or minute program by WDT_UNIT)
//--------------------------------------------------------------------------------------------------------
#define	WDT_CONFIGURATION				0x36	//  Configure WDT Function
#define		WDT_TIMEOUT_FLAG			0x40	//	When watchdog timeout.this bit will be set to 1.
#define		WDT_ENABLE					0x20	//	Enable watchdog timer
#define		WDT_PULSE					0x10	//	Configure WDT output mode
//	0:Level Mode
//	1:Pulse	Mode
#define		WDT_UNIT					0x08	//	Watchdog unit select.
//	0:Select second.
//	1:Select minute.
#define		WDT_LEVEL					0x04	//	When select level output mode:
//	0:Level low
//	1:Level high
#define		WDT_PSWIDTH_1MS				0x00	//	When select Pulse mode:	1	ms.
#define		WDT_PSWIDTH_20MS			0x01	//	When select Pulse mode:	20	ms.
#define		WDT_PSWIDTH_100MS			0x02	//	When select Pulse mode:	100	ms.
#define		WDT_PSWIDTH_4000MS			0x03	//	When select Pulse mode:	4	 s.
//--------------------------------------------------------------------------------------------------------


typedef struct F75111_Address
{
    BYTE bAddress;
    //BYTE bAddress2;
} F75111_Address;


bool F75111_Init();

bool F75111_GetDigitalInput_Pin(int);	//pin number 0-15
BYTE F75111_GetDigitalInput();
bool F75111_SetDigitalOutput_Pin(BYTE pin_number, bool pin_status);

void F75111_SetDigitalOutput(BYTE byteValue);
void F75111_SetDigitalOutput_2(BYTE byteValue);

BYTE F75111_GetWDTMode();
void F75111_SetWDTMode(BYTE dwvalue);

void F75111_SetWDTEnable    (BYTE byteTimer);
void F75111_SetWDTDisable   ();

#endif