// SMBus.h: interface for the SMBus class.
//
//////////////////////////////////////////////////////////////////////
#include "YjlDef.h"

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;


#pragma pack(1)

typedef struct
{
    U16 MapIoAddr;              // SMBus MapIO Address
    U16 VendorID;
    U16 DeviceID;
    U16 InstCount;
    U32 shmid;
    u32 OemMark;
    u32 UserOffset[4];
    u32 TempOffset;
} sBusMem;

#pragma pack()

//////////////////////////////////////////////////////////////////////////////////////////////////////

#define dSharedMemSize                        4096      //
#define dSharedMemName           _T("LexSMBusMem")      //
#define dSharedOemKey                  0x2E78654C      // 'Lex.'
// VendorID
#define dVendorID_Intel                     0x8086
#define dVendorID_VIA                       0x1106
#define dVendorID_AMD                       0x1022
#define dVendorID_NVIDIA                    0x10DE
// DeviceID (Intel) HOST_IOBASE=0x20
#define dDeviceID_Intel_82801DB_0           0x24C0      // 82801DB (ICH4) ª`·N : µL°Ï¶ôŒÒŠ¡Šsšú¡A€£šÏ¥Î
#define dDeviceID_Intel_82801DB_3           0x24C3      // 82801DB (ICH4) ª`·N : µL°Ï¶ôŒÒŠ¡Šsšú¡A€£šÏ¥Î
#define dDeviceID_Intel_82801EB_3           0x24D3      // 82801E (ICH5)  ª`·N : SMBHSTCFG_SPD_WD »Ý­n¹ê°µšÏ¥Î
#define dDeviceID_Intel_ESB_4               0x25A4      // 6300ESB
#define dDeviceID_Intel_ICH6_16             0x266A      // 82801F (ICH6)
#define dDeviceID_Intel_ESB2_17             0x269B      // 6310ESB/6320ESB
#define dDeviceID_Intel_ICH7_17             0x27DA      // 82801G (ICH7)
#define dDeviceID_Intel_ICH8_5              0x283E      // 82801H (ICH8)
#define dDeviceID_Intel_ICH9_6              0x2930      // 82801I (ICH9)
#define dDeviceID_Intel_EP80579_1           0x5032      // EP80579 (Tolapai)
#define dDeviceID_Intel_ICH10_4             0x3A30      // ICH10
#define dDeviceID_Intel_ICH10_5             0x3A60      // ICH10
#define dDeviceID_Intel_5_3400_SERIES       0x3B30      // 5/3400 Series (PCH)
#define dDeviceID_Intel_COUGARPOINT         0x1C22      // 6 Series (PCH)
#define dDeviceID_Intel_PATSBURG            0x1D22      // Patsburg (PCH)
#define dDeviceID_Intel_PATSBURG_IDF0       0x1D70      // Patsburg (PCH) IDF
#define dDeviceID_Intel_PATSBURG_IDF1       0x1D71      // Patsburg (PCH) IDF
#define dDeviceID_Intel_PATSBURG_IDF2       0x1D72      // Patsburg (PCH) IDF
#define dDeviceID_Intel_DH89XXCC            0x2330      // DH89xxCC (PCH)
#define dDeviceID_Intel_PANTHERPOINT        0x1E22      // Panther Point (PCH)
#define dDeviceID_Intel_LYNXPOINT           0x8C22      // Lynx Point (PCH)
#define dDeviceID_Intel_LYNXPOINT_LP        0x9C22      // Lynx Point-LP (PCH)
#define dDeviceID_Intel_AVOTON              0x1F3C      // Avoton (SOC)
#define dDeviceID_Intel_WELLSBURG           0x8D22      // Wellsburg (PCH)
#define dDeviceID_Intel_WELLSBURG_MS0       0x8D7D      // Wellsburg (PCH) MS
#define dDeviceID_Intel_WELLSBURG_MS1       0x8D7E      // Wellsburg (PCH) MS
#define dDeviceID_Intel_WELLSBURG_MS2       0x8D7F      // Wellsburg (PCH) MS
#define dDeviceID_Intel_COLETOCREEK         0x23B0      // Coleto Creek (PCH)
#define dDeviceID_Intel_GEMINILAKE          0x31D4      // Gemini Lake (SOC)
#define dDeviceID_Intel_WILDCATPOINT        0x8CA2      // Wildcat Point (PCH)
#define dDeviceID_Intel_WILDCATPOINT_LP     0x9CA2      // Wildcat Point-LP (PCH)
#define dDeviceID_Intel_BAYTRAIL            0x0F12      // BayTrail (SOC)
#define dDeviceID_Intel_BRASWELL            0x2292      // Braswell (SOC)
#define dDeviceID_Intel_SUNRISEPOINT_H      0xA123      // Sunrise Point-H (PCH) Sky_Lake
#define dDeviceID_Intel_SUNRISEPOINT_LP     0x9D23      // Sunrise Point-LP (PCH) Sky_Lake_U
#define dDeviceID_Intel_CDF                 0x18DF      // CDF (SOC)
#define dDeviceID_Intel_DNV                 0x19DF      // DNV (SOC)
#define dDeviceID_Intel_BROXTON             0x5AD4      // Broxton (SOC) Apollo_Lake
#define dDeviceID_Intel_LEWISBURG           0xA1A3      // Lewisburg (PCH)
#define dDeviceID_Intel_LEWISBURG_SSKU      0xA223      // Lewisburg Supersku (PCH)
#define dDeviceID_Intel_KABYLAKE_PCH_H      0xA2A3      // Kaby Lake PCH-H (PCH)
#define dDeviceID_Intel_CANNONLAKE_H        0xA323      // Cannon Lake-H (PCH) Coffee_Lake
#define dDeviceID_Intel_CANNONLAKE_LP       0x9DA3      // Cannon Lake-LP (PCH) Whisky_Lake
#define dDeviceID_Intel_CEDAR_FORK          0x18DF      // Cedar Fork (PCH)
#define dDeviceID_Intel_ICELAKE_LP          0x34A3      // Ice Lake-LP (PCH)
#define dDeviceID_Intel_COMETLAKE           0x02A3      // Comet Lake (PCH)
#define dDeviceID_Intel_ELKHART_LAKE        0x4B23      // Elkhart Lake (PCH)
#define dDeviceID_Intel_TIGERLAKE_LP        0xA0A3      // Tiger Lake-LP (PCH)
// DeviceID (VIA) HOST_IOBASE=0xD0
#define dDeviceID_VIA_8233_0                0x3074      // VT8233
#define dDeviceID_VIA_8233A                 0x3147      // VT8233A
#define dDeviceID_VIA_8235                  0x3177      // VT8235
#define dDeviceID_VIA_8237                  0x3227      // VT8237R
#define dDeviceID_VIA_8237A                 0x3337      // VT8237A
#define dDeviceID_VIA_8237S                 0x3372      // VT8237S
#define dDeviceID_VIA_8251                  0x3287      // VT8251
#define dDeviceID_VIA_CX700                 0x8324      // CX700
#define dDeviceID_VIA_VX800                 0x8353      // VX800/VX820
#define dDeviceID_VIA_VX855                 0x8409      // VX855/VX875
#define dDeviceID_VIA_VX900                 0x8410      // VX900
// Intel SMBus controller PCI configuration registers.
#define INTEL_SMBUS_HOST_VID                0x00        // Vendor Identification
#define INTEL_SMBUS_HOST_DID                0x02        // Device Identification
#define INTEL_SMBUS_HOST_IOBASE             0x20        // SMBus Base Address
#define INTEL_SMBUS_HOST_CONFIGURE          0x40        // Host Configuration
// Intel Host Configuration Register
#define INTEL_SMBUS_HOSTSC_HST_EN           0x01        // If set, the SMB controller is enabled to execute commands.
#define INTEL_SMBUS_HOSTSC_SMI_EN           0x02        // If set, any source of a SMBus interrupt will be routed to generate a special System Management Interrupt (SMI).
#define INTEL_SMBUS_HOSTSC_I2C_EN           0x04        // If set, some command protocols of the SMBus controller are changed in order to be able to communicate with I2C devices.
#define INTEL_SMBUS_HOSTSC_RESET            0x08        // If set, the SMBus state machine and logic is reset.
// VIA SMBus controller PCI configuration registers.
#define VIA_SMBUS_HOST_VID                  0x00        // Vendor Identification
#define VIA_SMBUS_HOST_DID                  0x02        // Device Identification
#define VIA_SMBUS_HOST_IOBASE               0xD0        // SMBus Base Address
#define VIA_SMBUS_HOST_CONFIGURE            0xD2        // Host Configuration
// VIA Host Configuration Register
#define VIA_SMBUS_HOSTSC_CONTROLER_ENABLE   0x01
#define VIA_SMBUS_HOSTSC_INTERRUPT_ENABLE   0x02
#define VIA_SMBUS_HOSTSC_CLOCK              0x04
#define VIA_SMBUS_HOSTSC_INTERRUPT_TYPE     0x08
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
/////////////////////////////////////////////////////////////////////////////////
// yu++ 20200227 for share memory

#define RC_NOT_ENOUGH_MEMORY	    65
#define RC_OBJECT_NOT_CREATED	    66
#define RC_MEMSIZE_ERROR	        67
//20210309 Add AMD V1000 R1000 by Nico↓↓↓
//----------------------------------------------------------------------------------
//AMD SMBUS ASL IO BASE
#define dDeviceID_AMD_V1000_R1000			0x790B		// V1000_R1000
#define AMD_V1000_R1000_SMBUS1				0x00		//SMBUS IO BASE(CO1)
#define AMD_V1000_R1000_SMBUS2				0x20		//ASL IO BASE(CO2)
//20210309 Add AMD V1000 R1000 by Nico↑↑↑


//----------------------------------------------------------------------------------
//	PCI Device Read/Write I/O
//----------------------------------------------------------------------------------
#define 	PCI_CONFIG_ADDR					0xCF8
#define 	PCI_CONFIG_DATA					0xCFC
//20210226 Add AMD V1000 R1000 by Nico↓↓↓
//----------------------------------------------------------------------------------
//	AMD Power Management (PM) Read/Write I/O
//----------------------------------------------------------------------------------
#define	AMD_PMIO_INDEX							        0x0CD6
#define	AMD_PMIO_DATA							        0x0CD7

//----------------------------------------------------------------------------------
//	AMD Power Menaget Power Management (PM) Register
//----------------------------------------------------------------------------------
#define		AMD_PM_DecodeEn_OFFSET0				        0x0		//	byte 1
#define		AMD_SMBusAsf_IO_EN					        0x0010	//	SmbusAsfIoEn. Read-write. Reset: 1. 1=Enable SMBus and ASF IO decoding. SMBUS and ASF IO ranges are
																//	defined in Smbus0AsfIoBase
#define		AMD_PM_DecodeEn_OFFSET1				        0x1		//	byte 2
#define		SmbusAsfIoBase						        0xFF00	//	Description: Specifiies SMBus and ASF IO base address.
																//	SMBus IO base = { Smbus0AsfIoBase[7:0],0x00 }.
																//	ASF IO base = { Smbus0AsfIoBase[7:0],0x20 }.
																//	By default SMBus IO base is 0xB00 and ASF IO base is 0xB20.
//----------------------------------------------------------------------------------
//	AMD　V1000 R1000 SMBus Host Controller
//----------------------------------------------------------------------------------
#define		AMD_V1000_R1000_SMBUS_HOST_DEVICE_ID		0x790B
#define		AMD_V1000_R1000_SMBUS_HOST_VENDOR_ID		0x1022
//20210226 Add AMD V1000 R1000 by Nico↑↑↑
//----------------------------------------------------------------------------------
//	Intel ICH4 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define 	INTEL_ICH4_VENDOR_ID				0x8086
#define 	INTEL_ICH4_DEVICE_ID				0x24C0
#define 	INTEL_ICH4_SMBUS_VENDOR_ID			0x8086
#define 	INTEL_ICH4_SMBUS_DEVICE_ID			0x24C3
//----------------------------------------------------------------------------------
#define     ICH4_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define     ICH4_SMBUS_HOST_CONFIGURE			0x40
#define     ICH4_SMBUS_HOST_HST_EN				0x01
#define     ICH4_SMBUS_HOST_SMI_EN				0x02
#define     ICH4_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel 945 ICH7 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_ICH7_VENDOR_ID				0x8086
#define		INTEL_ICH7_DEVICE_ID				0x2448

#define		INTEL_ICH7_SMBUS_VENDOR_ID			0x8086
#define		INTEL_ICH7_SMBUS_DEVICE_ID			0x27DA
//----------------------------------------------------------------------------------
#define		ICH7_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		ICH7_SMBUS_HOST_CONFIGURE			0x40
#define		ICH7_SMBUS_HOST_HST_EN				0x01
#define		ICH7_SMBUS_HOST_SMI_EN				0x02
#define		ICH7_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel 510&525 ICH8 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_ICH8_VENDOR_ID				0x8086
#define		INTEL_ICH8_DEVICE_ID				0x244E

#define		INTEL_ICH8_SMBUS_VENDOR_ID			0x8086
#define		INTEL_ICH8_SMBUS_DEVICE_ID			0x283E
//----------------------------------------------------------------------------------
#define		ICH8_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		ICH8_SMBUS_HOST_CONFIGURE			0x40
#define		ICH8_SMBUS_HOST_HST_EN				0x01
#define		ICH8_SMBUS_HOST_SMI_EN				0x02
#define		ICH8_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel 275 ICH10 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_ICH10_VENDOR_ID				0x8086
#define		INTEL_ICH10_DEVICE_ID				0x244E

#define		INTEL_ICH10_SMBUS_VENDOR_ID			0x8086
#define		INTEL_ICH10_SMBUS_DEVICE_ID			0x3A30
//----------------------------------------------------------------------------------
#define		ICH10_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		ICH10_SMBUS_HOST_CONFIGURE			0x40
#define		ICH10_SMBUS_HOST_HST_EN				0x01
#define		ICH10_SMBUS_HOST_SMI_EN				0x02
#define		ICH10_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel NM10 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_NM10_VENDOR_ID				0x8086
#define		INTEL_NM10_DEVICE_ID				0x2448

#define		INTEL_NM10_SMBUS_VENDOR_ID			0x8086
#define		INTEL_NM10_SMBUS_DEVICE_ID			0x27DA
//----------------------------------------------------------------------------------
#define		NM10_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		NM10_SMBUS_HOST_CONFIGURE			0x40
#define		NM10_SMBUS_HOST_HST_EN				0x01
#define		NM10_SMBUS_HOST_SMI_EN				0x02
#define		NM10_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel QM67 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_QM67_SMBUS_VENDOR_ID			0x8086
#define		INTEL_QM67_SMBUS_DEVICE_ID			0x1C22
//----------------------------------------------------------------------------------
#define		QM67_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		QM67_SMBUS_HOST_CONFIGURE			0x40
#define		QM67_SMBUS_HOST_HST_EN				0x01
#define		QM67_SMBUS_HOST_SMI_EN				0x02
#define		QM67_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel QM77 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_QM77_SMBUS_VENDOR_ID			0x8086
#define		INTEL_QM77_SMBUS_DEVICE_ID			0x1E22
//----------------------------------------------------------------------------------
#define		QM77_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		QM77_SMBUS_HOST_CONFIGURE			0x40
#define		QM77_SMBUS_HOST_HST_EN				0x01
#define		QM77_SMBUS_HOST_SMI_EN				0x02
#define		QM77_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel HM65 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_HM65_SMBUS_VENDOR_ID			0x8086
#define		INTEL_HM65_SMBUS_DEVICE_ID			0x1C22
//----------------------------------------------------------------------------------
#define		HM65_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		HM65_SMBUS_HOST_CONFIGURE			0x40
#define		HM65_SMBUS_HOST_HST_EN				0x01
#define		HM65_SMBUS_HOST_SMI_EN				0x02
#define		HM65_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel HM76 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_HM76_SMBUS_VENDOR_ID			0x8086
#define		INTEL_HM76_SMBUS_DEVICE_ID			0x1E22
//----------------------------------------------------------------------------------
#define		HM76_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		HM76_SMBUS_HOST_CONFIGURE			0x40
#define		HM76_SMBUS_HOST_HST_EN				0x01
#define		HM76_SMBUS_HOST_SMI_EN				0x02
#define		HM76_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel Bay Trail-I SoC Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_SOC_SMBUS_VENDOR_ID			0x8086
#define		INTEL_SOC_SMBUS_DEVICE_ID			0x0F12
//----------------------------------------------------------------------------------
#define		SOC_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		SOC_SMBUS_HOST_CONFIGURE			0x40
#define		SOC_SMBUS_HOST_HST_EN				0x01
#define		SOC_SMBUS_HOST_SMI_EN				0x02
#define		SOC_SMBUS_HOST_I2C_EN				0x04

//20170512 Add Apollo_Lake by Nico↓↓↓
//	Intel Apollo Lake SoC Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Apollo_Lake_SOC_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Apollo_Lake_SOC_SMBUS_DEVICE_ID			0x5AD4
//----------------------------------------------------------------------------------
#define		Apollo_Lake_SOC_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Apollo_Lake_SOC_SMBUS_HOST_CONFIGURE			0x40
#define		Apollo_Lake_SOC_SMBUS_HOST_HST_EN				0x01
#define		Apollo_Lake_SOC_SMBUS_HOST_SMI_EN				0x02
#define		Apollo_Lake_SOC_SMBUS_HOST_I2C_EN				0x04

//----------------------------------------------------------------------------------
//	Intel Sky Lake SoC Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Sky_Lake_SOC_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Sky_Lake_SOC_SMBUS_DEVICE_ID			0xA123
//----------------------------------------------------------------------------------
#define		Sky_Lake_SOC_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Sky_Lake_SOC_SMBUS_HOST_CONFIGURE			0x40
#define		Sky_Lake_SOC_SMBUS_HOST_HST_EN				0x01
#define		Sky_Lake_SOC_SMBUS_HOST_SMI_EN				0x02
#define		Sky_Lake_SOC_SMBUS_HOST_I2C_EN				0x04
//20170512 Add Sky_Lake by Nico↑↑↑


//20170830 Add Sky_Lake-U by Tracy↓↓↓
//----------------------------------------------------------------------------------
//	Intel Sky Lake SoC Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Sky_Lake_U_SOC_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Sky_Lake_U_SOC_SMBUS_DEVICE_ID			0x9D23
//----------------------------------------------------------------------------------
#define		Sky_Lake_U_SOC_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Sky_Lake_U_SOC_SMBUS_HOST_CONFIGURE			0x40
#define		Sky_Lake_U_SOC_SMBUS_HOST_HST_EN				0x01
#define		Sky_Lake_U_SOC_SMBUS_HOST_SMI_EN				0x02
#define		Sky_Lake_U_SOC_SMBUS_HOST_I2C_EN				0x04
// Add Sky_Lake-U by Tracy↑↑↑
//----------------------------------------------------------------------------------

//20190430 Add Coffee_Lake-S by Nico↓↓↓
//----------------------------------------------------------------------------------
//	Intel Coffeelake–S Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Coffee_Lake_SOC_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Coffee_Lake_SOC_SMBUS_DEVICE_ID			0xA323
//----------------------------------------------------------------------------------
#define		Coffee_Lake_SOC_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Coffee_Lake_SOC_SMBUS_HOST_CONFIGURE			0x40
#define		Coffee_Lake_SOC_SMBUS_HOST_HST_EN				0x01
#define		Coffee_Lake_SOC_SMBUS_HOST_SMI_EN				0x02
#define		Coffee_Lake_SOC_SMBUS_HOST_I2C_EN				0x04
//20190430 Add Coffee_Lake-S by Nico↑↑↑

//20190510 Add Whisky lake by KK↓↓↓
//----------------------------------------------------------------------------------
//	Intel Whisky lake Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Whisky_Lake_SOC_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Whisky_Lake_SOC_SMBUS_DEVICE_ID			0x9DA3
//----------------------------------------------------------------------------------
#define		Whisky_Lake_SOC_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Whisky_Lake_SOC_SMBUS_HOST_CONFIGURE			0x40
#define		Whisky_Lake_SOC_SMBUS_HOST_HST_EN				0x01
#define		Whisky_Lake_SOC_SMBUS_HOST_SMI_EN				0x02
#define		Whisky_Lake_SOC_SMBUS_HOST_I2C_EN				0x04
// Add whisky lake by KK↑↑↑

//20210802 Add Elkhart lake by Nico↓↓↓
//----------------------------------------------------------------------------------
//	Intel Elkhart lake Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Elkhart_Lake_STD_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Elkhart_Lake_STD_SMBUS_DEVICE_ID			0x4B23
//----------------------------------------------------------------------------------
#define		Elkhart_Lake_STD_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Elkhart_Lake_STD_SMBUS_HOST_CONFIGURE			0x40
#define		Elkhart_Lake_STD_SMBUS_HOST_HST_EN				0x01
#define		Elkhart_Lake_STD_SMBUS_HOST_SMI_EN				0x02
#define		Elkhart_Lake_STD_SMBUS_HOST_I2C_EN				0x04
// Add Elkhart lake by Nico↑↑↑

//20210803 Add Comet lake by Nico↓↓↓
//----------------------------------------------------------------------------------
//	Intel Comet lake Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Comet_Lake_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Comet_Lake_SMBUS_DEVICE_ID			0x02A3
//----------------------------------------------------------------------------------
#define		Comet_Lake_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Comet_Lake_SMBUS_HOST_CONFIGURE			    0x40
#define		Comet_Lake_SMBUS_HOST_HST_EN				0x01
#define		Comet_Lake_SMBUS_HOST_SMI_EN				0x02
#define		Comet_Lake_SMBUS_HOST_I2C_EN				0x04
//----------------------------------------------------------------------------------
//	Intel Comet lake-SP Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define		INTEL_Comet_Lake_SP_SMBUS_VENDOR_ID			0x8086
#define		INTEL_Comet_Lake_SP_SMBUS_DEVICE_ID			0x06A3
//----------------------------------------------------------------------------------
#define		Comet_Lake_SP_SMBUS_HOST_IOBASE				0x20
//----------------------------------------------------------------------------------
#define		Comet_Lake_SP_SMBUS_HOST_CONFIGURE			0x40
#define		Comet_Lake_SP_SMBUS_HOST_HST_EN				0x01
#define		Comet_Lake_SP_SMBUS_HOST_SMI_EN				0x02
#define		Comet_Lake_SP_SMBUS_HOST_I2C_EN				0x04
// Add Comet lake by Nico↑↑↑

//----------------------------------------------------------------------------------
//	VIA VT8237 Vendor ID & Device ID
//----------------------------------------------------------------------------------
#define 	VIA_VT8237_BUS_CTRL_VENDOR_ID			0x1106
#define 	VIA_VT8237_BUS_CTRL_DEVICE_ID			0x3227
//----------------------------------------------------------------------------------
#define		VT8237_SMBUS_HOST_IOBASE			0xD0
//----------------------------------------------------------------------------------
#define		VT8237_SMBUS_HOST_CONFIGURE			0xD2
#define		VT8237_SMBUS_HOST_CONTROLER_ENABLE		0x01
#define		VT8237_SMBUS_HOST_INTERRUPT_ENABLE		0x02
#define		VT8237_SMBUS_HOST_INTERRUPT_TYPE		0x08
//----------------------------------------------------------------------------------
#define 	VIA_CX700M_BUS_CTRL_VENDOR_ID			0x1106
#define 	VIA_CX700M_BUS_CTRL_DEVICE_ID			0x8324
//----------------------------------------------------------------------------------
#define		CX700M_SMBUS_HOST_IOBASE			0xD0
//----------------------------------------------------------------------------------
#define		CX700M_SMBUS_HOST_CONFIGURE			0xD2
#define		CX700M_SMBUS_HOST_CONTROLER_ENABLE		0x01
#define		CX700M_SMBUS_HOST_INTERRUPT_ENABLE		0x02
#define		CX700M_SMBUS_HOST_INTERRUPT_TYPE		0x08
#define		CX700M_SMBUS_HOST_CLOCK				0x04
//----------------------------------------------------------------------------------
//	VIA VX900 Vendor ID / Devices ID & Bus-Specific configuration register
//----------------------------------------------------------------------------------
#define 	VIA_VX900_BUS_CTRL_VENDOR_ID			0x1106
#define 	VIA_VX900_BUS_CTRL_DEVICE_ID			0x8410
#define		VX900_SMBUS_HOST_IOBASE				0xD0
#define		VX900_SMBUS_HOST_CONFIGURE			0xD2
#define		VX900_SMBUS_HOST_CONTROLER_ENABLE		0x01

//-----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//		Register of VIA & Intel
//----------------------------------------------------------------------------------
#define		SMBHSTSTS		0x00	// SMBus Host  Status Register Offset
#define		SMBHSTSTS_BUSY		0x01	// SMBus Host -> 0000-0001 Busy
#define		SMBHSTSTS_INTR		0x02	// SMBus Host -> 0000-0010 Interrupt / complection
#define		SMBHSTSTS_ERROR		0x04	// SMBus Host -> 0000-0100 Error
#define		SMBHSTSTS_COLLISION	0x08	// SMBus Host -> 0000-1000 Collistion
#define		SMBHSTSTS_FAILED	0x10	// SMBus Host -> 0001-0000 Failed
//----------------------------------------------------------------------------------
#define		SMBHSTCNT		0x02	// SMBus Host Contorl Register Offset
#define		SMBHSTCNT_KILL		0x02	// SMBus Host Contorl -> 0000 0010 Kill
#define		SMBHSTCNT_QUICK		0x00	// SMBus Host Contorl -> 0000 0000 quick (default)
#define		SMBHSTCNT_SENDRECV	0x04	// SMBus Host Contorl -> 0000 0100 Byte
#define		SMBHSTCNT_BYTE		0x08	// SMBus Host Contorl -> 0000 1000 Byte Data
#define		SMBHSTCNT_WORD		0x0c	// SMBus Host Contorl -> 0000 1100 Word Data
						// Write/Read Word
#define		SMBHSTCNT_BLOCK		0x14	// SMBus Host Contorl -> 0001 0100 Block
#define		SMBHSTCNT_START		0x40	// SMBus Host Contorl -> 0100 0000 Start
//----------------------------------------------------------------------------------
#define	SMBHSTCMD			0x03	// SMBus Host Command		Register Offset
#define	SMBHSTADD			0x04	// SMBus Host Address		Register Offset
#define	SMBHSTDAT0			0x05	// SMBus Host Data0			Register Offset
										// SMBus Host Block Counter	Register Offset
#define	SMBHSTDAT1			0x06	// SMBus Host Data1			Register Offset
#define	SMBBLKDAT			0x07	// SMBus Host Block	Data	Register Offset

//----------------------------------------------------------------------------------
//		Register of VIA only
//----------------------------------------------------------------------------------
#define	SMBHSLVSTS			0x01		// SMBus Slave Status Register Offset
//----------------------------------------------------------------------------------
#define	SMBSLVCNT			0x08		// SMBus Slave  Control
#define	SMBSHDWCMD			0x09		// SMBus Shadow Command
#define	SMBSLVEVT			0x0a		// SMBus Slave  Event
#define	SMBSLVDAT			0x0c		// SMBus Slave  Data
//----------------------------------------------------------------------------------
#define	SMBUS_TIMEOUT		100
//----------------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////////////////////////////

static int gSMBusMapObject = 0;
static sBusMem *gSMBusMemPtr = NULL;
static int gnLocalInstCount = 0;
extern WORD m_SMBusMapIoAddr,m_SMBusMapIoAddr_2;

typedef struct platform{
    bool INTEL;
    bool AMD;
}platform;

//////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
// Name        : PCI_Read
// Description :
// Arguments   :
// Return      : Byte
//---------------------------------------------------------------------------
DWORD PCI_Read (int size_t);

//--------------------------------------------------------------------------
// Name        : PCI_Write
// Description :
// Arguments   :
// Return      : None
//---------------------------------------------------------------------------
void PCI_Write(DWORD dwDataVal,int size_t);

//--------------------------------------------------------------------------
// Name        : PCI_AutoDetect
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool PCI_AutoDetect();

//--------------------------------------------------------------------------
// Name        : Get_ICH4_SMBusIoAddr
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool Get_ICH4_SMBusIoAddr(DWORD dwIOAddr, DWORD dwConfigure, DWORD dwCtlEnable, DWORD dwIOBase, DWORD dwBitwise);

//--------------------------------------------------------------------------
// Name        : GetSMBusIoAddr
// Description : Get SMBus I/O Address
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool GetSMBusIoAddr(DWORD dwIOAddr, DWORD dwConfigure, DWORD dwCtlEnable, DWORD dwIOBase, DWORD dwBitwise);

//--------------------------------------------------------------------------
// Name        : Get_AMD_SMBusIoAddr
// Description : Get AMD SMBus I/O Address
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
//bool Get_AMD_SMBusIoAddr(DWORD dwIOAddr, DWORD dwConfigure, DWORD dwCtlEnable, DWORD dwIOBase, DWORD dwBitwise);
bool Get_AMD_SMBusIoAddr();
//--------------------------------------------------------------------------
// Name        : AMD_PMIO_Write
// Description : AMD PMIO Write
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void AMD_PMIO_Write(DWORD dwIndexVal, DWORD dwDataVal);
//--------------------------------------------------------------------------
// Name        : AMD_PMIO_Read
// Description : AMD PMIO Read
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
DWORD AMD_PMIO_Read(DWORD dwIndexVal);


//--------------------------------------------------------------------------
// Name        : SMBusIoRead
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
BYTE SMBusIoRead(BYTE byteOffset);

//--------------------------------------------------------------------------
// Name        : SMBusIoWrite
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void SMBusIoWrite(BYTE byteOffset,BYTE byteData);

//--------------------------------------------------------------------------
// Name        : SMBus_Install
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
BOOL SMBus_Install();

//--------------------------------------------------------------------------
// Name        : SMBus_Uninstall
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void SMBus_Uninstall();

//--------------------------------------------------------------------------
// Name        : SMBus_CreateSharedMem
// Description : 建立共享記憶體
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
static inline BOOL SMBus_CreateSharedMem();

//--------------------------------------------------------------------------
// Name        : SMBus_DestorySharedMem
// Description : 刪除共享記憶體
// Arguments   :
// Return      : None
//---------------------------------------------------------------------------
static inline void SMBus_DestorySharedMem();

////--------------------------------------------------------------------------
//// Name        : SMBus_ReadShareMem
//// Description :
//// Arguments   :
//// Return      : None
////---------------------------------------------------------------------------
//static inline void SMBus_ReadShareMem();

//--------------------------------------------------------------------------
// Name        : SMBus_Clear
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void SMBus_Clear();

//--------------------------------------------------------------------------
// Name        : SMBus_Wait
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
int	SMBus_Wait();

//--------------------------------------------------------------------------
// Name        : SMBus_Busy
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_Busy();

//--------------------------------------------------------------------------
// Name        : SMBus_CheckDevice
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_CheckDevice(BYTE byteDeviceAddress);
//20210304 add by Nico ↓↓↓
//--------------------------------------------------------------------------
// Name        : SMBus_CheckChip
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_CheckChip(BYTE byteSlave, WORD deviceID, BYTE CHIP_ID_REGISTER2, BYTE CHIP_ID_REGISTER1);
//20210304 add by Nico ↑↑↑
//--------------------------------------------------------------------------
// Name        : SMBus_WriteByte
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
int	SMBus_WriteByte(BYTE byteSlave,BYTE pCmd,BYTE  pByte);

//--------------------------------------------------------------------------
// Name        : SMBus_ReadByte
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
int	SMBus_ReadByte(BYTE byteSlave,BYTE pCmd,BYTE *pByte);

//--------------------------------------------------------------------------
// Name        : SMBus_WriteWord
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_WriteWord(BYTE tSlaveAddr , BYTE tCmd , WORD tWord);

//--------------------------------------------------------------------------
// Name        : SMBus_ReadWord
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_ReadWord(BYTE byteSlave,BYTE pCmd,WORD *pWord);

//--------------------------------------------------------------------------
// Name        : SMBus_WriteBlock
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_WriteBlock(BYTE tSlaveAddr, BYTE tCmd, BYTE *tBlock);

//--------------------------------------------------------------------------
// Name        : SMBus_ReadBlock
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_ReadBlock(BYTE tSlaveAddr,BYTE tCmd,BYTE *tBlock);

void SMBus_Fix(void);

