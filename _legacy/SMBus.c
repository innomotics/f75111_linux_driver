// SMBus.cpp: implementation of the SMBus class.
//
//////////////////////////////////////////////////////////////////////

#include "SMBus.h"

platform Platform;//20210305 add by Nico


struct timespec tout;
//tout.tv_sec = 50000;
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// PCI Device Write/Read Function
//////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
// Name        : PCI_Read
// Description :
// Arguments   :
// Return      : Byte
//---------------------------------------------------------------------------
DWORD PCI_Read(int size_t)
{
	DWORD dwAddrVal;

	//GetPortVal(PCI_CONFIG_DATA,&dwAddrVal,size_t);
	dwAddrVal = inl(PCI_CONFIG_DATA);
    usleep(10);

	return dwAddrVal;
}

//--------------------------------------------------------------------------
// Name        : PCI_Write
// Description :
// Arguments   :
// Return      : None
//---------------------------------------------------------------------------
void PCI_Write(DWORD dwDataVal,int size_t)
{
	//SetPortVal(PCI_CONFIG_ADDR, dwDataVal,size_t);
	outl( dwDataVal, PCI_CONFIG_ADDR );
	usleep(10);
}

//--------------------------------------------------------------------------
// Name        : PCI_AutoDetect
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool PCI_AutoDetect()
{
    if( gSMBusMemPtr == NULL )
        return false;

    if( gSMBusMemPtr->VendorID != 0 )
        return true;

    //=================================================//
    DWORD BITWISE_TABLE [] = { 0xFF00, 0xFFF0 };

    typedef struct _PCI_DEVICE_ST
    {
        DWORD dwVendorID;
        DWORD dwDeviceID;
        DWORD dwConfigure;
        DWORD dwCtlEnable;
        DWORD dwIOBase;
        DWORD dwBitwise;
    } PCI_DEVICE_ST;

    PCI_DEVICE_ST PCI_DEVICE_TABLE [] =
    {
        { VIA_VT8237_BUS_CTRL_VENDOR_ID, VIA_VT8237_BUS_CTRL_DEVICE_ID, VT8237_SMBUS_HOST_CONFIGURE, VT8237_SMBUS_HOST_CONTROLER_ENABLE, VT8237_SMBUS_HOST_IOBASE, BITWISE_TABLE[0] },
        { VIA_CX700M_BUS_CTRL_VENDOR_ID, VIA_CX700M_BUS_CTRL_DEVICE_ID, CX700M_SMBUS_HOST_CONFIGURE, CX700M_SMBUS_HOST_CONTROLER_ENABLE, CX700M_SMBUS_HOST_IOBASE, BITWISE_TABLE[0] },
        { VIA_VX900_BUS_CTRL_VENDOR_ID,  VIA_VX900_BUS_CTRL_DEVICE_ID,  VX900_SMBUS_HOST_CONFIGURE,  VX900_SMBUS_HOST_CONTROLER_ENABLE,  VX900_SMBUS_HOST_IOBASE,  BITWISE_TABLE[0] },

        { INTEL_ICH4_VENDOR_ID,        INTEL_ICH4_DEVICE_ID,        ICH4_SMBUS_HOST_CONFIGURE,  ICH4_SMBUS_HOST_HST_EN,  ICH4_SMBUS_HOST_IOBASE,  BITWISE_TABLE[0] },
        { INTEL_ICH7_SMBUS_VENDOR_ID,  INTEL_ICH7_SMBUS_DEVICE_ID,  ICH7_SMBUS_HOST_CONFIGURE,  ICH7_SMBUS_HOST_HST_EN,  ICH7_SMBUS_HOST_IOBASE,  BITWISE_TABLE[0] },
        { INTEL_ICH8_SMBUS_VENDOR_ID,  INTEL_ICH8_SMBUS_DEVICE_ID,  ICH8_SMBUS_HOST_CONFIGURE,  ICH8_SMBUS_HOST_HST_EN,  ICH8_SMBUS_HOST_IOBASE,  BITWISE_TABLE[0] },
        { INTEL_ICH10_SMBUS_VENDOR_ID, INTEL_ICH10_SMBUS_DEVICE_ID, ICH10_SMBUS_HOST_CONFIGURE, ICH10_SMBUS_HOST_HST_EN, ICH10_SMBUS_HOST_IOBASE, BITWISE_TABLE[0] },

        { INTEL_NM10_SMBUS_VENDOR_ID,  INTEL_NM10_SMBUS_DEVICE_ID,  NM10_SMBUS_HOST_CONFIGURE,  NM10_SMBUS_HOST_HST_EN,  NM10_SMBUS_HOST_IOBASE, BITWISE_TABLE[0] },

        { INTEL_QM67_SMBUS_VENDOR_ID,  INTEL_QM67_SMBUS_DEVICE_ID,  QM67_SMBUS_HOST_CONFIGURE,  QM67_SMBUS_HOST_HST_EN,  QM67_SMBUS_HOST_IOBASE, BITWISE_TABLE[1] },
        { INTEL_QM77_SMBUS_VENDOR_ID,  INTEL_QM77_SMBUS_DEVICE_ID,  QM77_SMBUS_HOST_CONFIGURE,  QM77_SMBUS_HOST_HST_EN,  QM77_SMBUS_HOST_IOBASE, BITWISE_TABLE[1] },
        { INTEL_HM65_SMBUS_VENDOR_ID,  INTEL_HM65_SMBUS_DEVICE_ID,  HM65_SMBUS_HOST_CONFIGURE,  HM65_SMBUS_HOST_HST_EN,  HM65_SMBUS_HOST_IOBASE, BITWISE_TABLE[1] },
        { INTEL_HM76_SMBUS_VENDOR_ID,  INTEL_HM76_SMBUS_DEVICE_ID,  HM76_SMBUS_HOST_CONFIGURE,  HM76_SMBUS_HOST_HST_EN,  HM76_SMBUS_HOST_IOBASE, BITWISE_TABLE[1] },
        { INTEL_SOC_SMBUS_VENDOR_ID,   INTEL_SOC_SMBUS_DEVICE_ID,   SOC_SMBUS_HOST_CONFIGURE,   SOC_SMBUS_HOST_HST_EN,   SOC_SMBUS_HOST_IOBASE,  BITWISE_TABLE[1] },

        { INTEL_Apollo_Lake_SOC_SMBUS_VENDOR_ID, INTEL_Apollo_Lake_SOC_SMBUS_DEVICE_ID, Apollo_Lake_SOC_SMBUS_HOST_CONFIGURE, Apollo_Lake_SOC_SMBUS_HOST_HST_EN, Apollo_Lake_SOC_SMBUS_HOST_IOBASE, BITWISE_TABLE[1] },
        { INTEL_Sky_Lake_SOC_SMBUS_VENDOR_ID,    INTEL_Sky_Lake_SOC_SMBUS_DEVICE_ID,    Sky_Lake_SOC_SMBUS_HOST_CONFIGURE,    Sky_Lake_SOC_SMBUS_HOST_HST_EN,    Sky_Lake_SOC_SMBUS_HOST_IOBASE,    BITWISE_TABLE[1] },
        { INTEL_Sky_Lake_U_SOC_SMBUS_VENDOR_ID,  INTEL_Sky_Lake_U_SOC_SMBUS_DEVICE_ID,  Sky_Lake_U_SOC_SMBUS_HOST_CONFIGURE,  Sky_Lake_U_SOC_SMBUS_HOST_HST_EN,  Sky_Lake_U_SOC_SMBUS_HOST_IOBASE,  BITWISE_TABLE[1] },
        { INTEL_Coffee_Lake_SOC_SMBUS_VENDOR_ID, INTEL_Coffee_Lake_SOC_SMBUS_DEVICE_ID, Coffee_Lake_SOC_SMBUS_HOST_CONFIGURE, Coffee_Lake_SOC_SMBUS_HOST_HST_EN, Coffee_Lake_SOC_SMBUS_HOST_IOBASE, BITWISE_TABLE[1] },
        { INTEL_Whisky_Lake_SOC_SMBUS_VENDOR_ID, INTEL_Whisky_Lake_SOC_SMBUS_DEVICE_ID, Whisky_Lake_SOC_SMBUS_HOST_CONFIGURE, Whisky_Lake_SOC_SMBUS_HOST_HST_EN, Whisky_Lake_SOC_SMBUS_HOST_IOBASE, BITWISE_TABLE[1] },
        { INTEL_Elkhart_Lake_STD_SMBUS_VENDOR_ID,INTEL_Elkhart_Lake_STD_SMBUS_DEVICE_ID,Elkhart_Lake_STD_SMBUS_HOST_CONFIGURE, Elkhart_Lake_STD_SMBUS_HOST_HST_EN, Elkhart_Lake_STD_SMBUS_HOST_IOBASE, BITWISE_TABLE[1]},
        { INTEL_Comet_Lake_SMBUS_VENDOR_ID,INTEL_Comet_Lake_SMBUS_DEVICE_ID,Comet_Lake_SMBUS_HOST_CONFIGURE, Comet_Lake_SMBUS_HOST_HST_EN, Comet_Lake_SMBUS_HOST_IOBASE, BITWISE_TABLE[1]},
        { INTEL_Comet_Lake_SP_SMBUS_VENDOR_ID,INTEL_Comet_Lake_SP_SMBUS_DEVICE_ID,Comet_Lake_SP_SMBUS_HOST_CONFIGURE, Comet_Lake_SP_SMBUS_HOST_HST_EN, Comet_Lake_SP_SMBUS_HOST_IOBASE, BITWISE_TABLE[1]},
        { AMD_V1000_R1000_SMBUS_HOST_VENDOR_ID, AMD_V1000_R1000_SMBUS_HOST_DEVICE_ID, AMD_PM_DecodeEn_OFFSET0,AMD_SMBusAsf_IO_EN,SmbusAsfIoBase, BITWISE_TABLE[1] }//20210305 add by Nico
    };

    int nTableSize = sizeof(PCI_DEVICE_TABLE) / sizeof(PCI_DEVICE_TABLE[0]);

    //=================================================//
    DWORD dwResult = 0x0;
    DWORD dwIOAddr = 0x0;

    DWORD dwVID = 0x0;
    DWORD dwDID = 0x0;

    int nRet = false;

    for( int PCI_Bus = 0; PCI_Bus < 5; PCI_Bus++ )
    {
        for( int PCI_Device = 0; PCI_Device < 32; PCI_Device++ )
        {
            for( int PCI_Function = 0; PCI_Function < 8; PCI_Function++ )
            {
                dwIOAddr = 0x80000000 + (PCI_Bus * 0x10000) + (PCI_Device * 0x800) + (PCI_Function * 0x100);

                PCI_Write( dwIOAddr, 4 );
                dwResult = PCI_Read(4);

                dwVID = dwResult & 0xFFFF;
                dwDID = dwResult >> 16;

                for( int i = 0; i < nTableSize; i++ )
                {
                    if( dwVID == PCI_DEVICE_TABLE[i].dwVendorID &&
                        dwDID == PCI_DEVICE_TABLE[i].dwDeviceID )
                    {
                        if( dwVID == INTEL_ICH4_VENDOR_ID &&
                            dwDID == INTEL_ICH4_DEVICE_ID )
                        {
                            nRet = Get_ICH4_SMBusIoAddr( dwIOAddr, PCI_DEVICE_TABLE[i].dwConfigure, PCI_DEVICE_TABLE[i].dwCtlEnable,
                                                       PCI_DEVICE_TABLE[i].dwIOBase, PCI_DEVICE_TABLE[i].dwBitwise );
                        }
                        //20210309 add by Nico ↓↓↓
                        else if(dwVID == AMD_V1000_R1000_SMBUS_HOST_VENDOR_ID &&
                                dwDID == AMD_V1000_R1000_SMBUS_HOST_DEVICE_ID )
                        {
                            /*nRet = Get_AMD_SMBusIoAddr(dwIOAddr, PCI_DEVICE_TABLE[i].dwConfigure, PCI_DEVICE_TABLE[i].dwCtlEnable,
                                                    PCI_DEVICE_TABLE[i].dwIOBase, PCI_DEVICE_TABLE[i].dwBitwise);*/
                            nRet = Get_AMD_SMBusIoAddr();

                        }
                        //20210309 add by Nico ↑↑↑
                        //=================================================//
                         else
                        {
                            nRet = GetSMBusIoAddr( dwIOAddr, PCI_DEVICE_TABLE[i].dwConfigure, PCI_DEVICE_TABLE[i].dwCtlEnable ,
                                                  PCI_DEVICE_TABLE[i].dwIOBase, PCI_DEVICE_TABLE[i].dwBitwise );
                        }

                        if( nRet == true )
                        {
                            gSMBusMemPtr->VendorID = PCI_DEVICE_TABLE[i].dwVendorID;
                            gSMBusMemPtr->DeviceID = PCI_DEVICE_TABLE[i].dwDeviceID;

                            return true;
                        }
                    }
                }
            }
        }
    }
	//printf("AutoDetect_IOBase : Can't Found Any SMBus Controller!\n");
	return false;
}

//--------------------------------------------------------------------------
// Name        : Get_ICH4_SMBusIoAddr
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool Get_ICH4_SMBusIoAddr(DWORD dwIOAddr, DWORD dwConfigure, DWORD dwCtlEnable, DWORD dwIOBase, DWORD dwBitwise)
{
    DWORD dwIOAddrTemp = 0x0;
    DWORD dwResult = 0x0;
    //Platform.INTEL=true;//20210309 add By Nico

    for( int PCI_Function = 0; PCI_Function < 8; PCI_Function++ )
    {
        dwIOAddrTemp = dwIOAddr + (PCI_Function * 0x100);

        PCI_Write( dwIOAddrTemp, 4 );
        dwResult = PCI_Read(4);

        if( (dwResult & 0xFFFF) == INTEL_ICH4_SMBUS_VENDOR_ID &&
            (dwResult >> 16) == INTEL_ICH4_SMBUS_DEVICE_ID )
        {
            return GetSMBusIoAddr( dwIOAddr, dwConfigure, dwCtlEnable, dwIOBase, dwBitwise );
        }
    }

    return false;
}

//20210309 add by Nico ↓↓↓
//bool Get_AMD_SMBusIoAddr(DWORD dwIOAddr, DWORD dwConfigure, DWORD dwCtlEnable, DWORD dwIOBase, DWORD dwBitwise)
bool Get_AMD_SMBusIoAddr()
{
    DWORD dwResult;
    //Platform.AMD=true;

    dwResult = AMD_PMIO_Read(AMD_PM_DecodeEn_OFFSET0);
    if (dwResult & AMD_SMBusAsf_IO_EN)
    {
        //printf("AMD R1000 :  SMBus and ASF IO decoding  Enable!\n");
    }
    else
    {
        //printf("AMD R1000 :  SMBus and ASF IO decoding  Disable!\n");
        return false;
    }
    dwResult = AMD_PMIO_Read(AMD_PM_DecodeEn_OFFSET1);
    gSMBusMemPtr->MapIoAddr = ((dwResult << 8) & SmbusAsfIoBase)+ AMD_V1000_R1000_SMBUS2;
    //printf("m_SMBusMapIoAddr = 0x%x", gSMBusMemPtr->MapIoAddr);

    return true;
}
//20210309 add by Nico ↑↑↑

//--------------------------------------------------------------------------
// Name        : GetSMBusIoAddr
// Description : Get SMBus I/O Address
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool GetSMBusIoAddr(DWORD dwIOAddr, DWORD dwConfigure, DWORD dwCtlEnable, DWORD dwIOBase, DWORD dwBitwise)
{
    PCI_Write( (dwIOAddr + dwConfigure), 4 );

    //==========================//
    DWORD dwResult = PCI_Read(2);

    if( (dwResult & dwCtlEnable) == 0 )
        return false;

    //==========================//
    int nRet = false;

    PCI_Write( (dwIOAddr + dwIOBase), 4 );

    if( gSMBusMemPtr != NULL )
    {
        gSMBusMemPtr->MapIoAddr = (WORD) (PCI_Read(4) & dwBitwise );
        nRet = true;
    }

    return nRet;
}

//////////////////////////////////////////////////////////////////////
// VT8237 SMBus Mapping I/O read/write
//////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
// Name        : SMBusIoWrite
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void SMBusIoWrite(BYTE byteOffset,BYTE byteData)
{
    if( gSMBusMemPtr == NULL )
        return;

    //==========================//
    outb( byteData, (gSMBusMCIO_LED_FLASH_f75111emPtr->MapIoAddr + byteOffset) );

    usleep(10);
}

//--------------------------------------------------------------------------
// Name        : SMBusIoRead
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
BYTE SMBusIoRead(BYTE byteOffset)
{
    if( gSMBusMemPtr == NULL )
        return (0x0);

    //==========================//
    DWORD dwAddrVal;
    dwAddrVal = inb((gSMBusMemPtr->MapIoAddr + byteOffset));

    usleep(10);

    return (BYTE)(dwAddrVal & 0x0FF);
}

//////////////////////////////////////////////////////////////////////
// Normal SMBus Function
//////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
// Name        : SMBus_Install
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
BOOL SMBus_Install(void)
{
    int nRet = SMBus_CreateSharedMem();
	nRet = SMBus_CreateSharedMem();
    if( nRet == TRUE )
    {
        if( gSMBusMemPtr->InstCount == 0 ||
            gSMBusMemPtr->OemMark != dSharedOemKey )
        {
		nRet = PCI_AutoDetect();
		gSMBusMemPtr->OemMark = dSharedOemKey;
		pthread_mutex_init( &gSMBusMemPtr->LockSection, NULL );
		//&gSMBusMemPtr->LockSection = PTHREAD_MUTEX_INITIALIZER;
			
		pthread_mutex_lock(&gSMBusMemPtr->LockSection);
		if( gSMBusMemPtr->VendorID == dVendorID_Intel )
			SMBusIoWrite( SMBAUXCTL, SMBusIoRead(SMBAUXCTL) & ~(SMBAUXCTL_CRC | SMBAUXCTL_E32B) );
		pthread_mutex_unlock(&gSMBusMemPtr->LockSection);
		
           
        }
        //20210310 add by Nico ↓↓↓
        //select platform INTEL/AMD
        if (gSMBusMemPtr->VendorID == dVendorID_Intel )
        {
            Platform.INTEL=true;
        }
        else if( gSMBusMemPtr->VendorID == dVendorID_AMD )
        {
            Platform.AMD=true;
        }
        //20210310 add by Nico ↑↑↑
        gSMBusMemPtr->InstCount++;
        gnLocalInstCount++;
    }

    //printf("[SMBus Info] Access SMBus count = %d \n",gSMBusMemPtr->InstCount );
    return nRet;
}

void SMBus_Fix(void)
{
	gSMBusMemPtr->InstCount = 0;
	gnLocalInstCount=0;
	SMBus_DestorySharedMem();
}
//--------------------------------------------------------------------------
// Name        : SMBus_Uninstall
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void SMBus_Uninstall(void)
{
    if( gnLocalInstCount > 0 )
        gnLocalInstCount--;

    //===========================================================//
    if( gSMBusMemPtr != NULL )
    {
        if( gSMBusMemPtr->InstCount > 0 )
            gSMBusMemPtr->InstCount--;

        if( gSMBusMemPtr->InstCount == 0 )
            pthread_mutex_destroy(&gSMBusMemPtr->LockSection);

        else
        {
            pthread_mutex_lock(&(gSMBusMemPtr->LockSection));
            pthread_mutex_unlock(&(gSMBusMemPtr->LockSection));
        }

        SMBus_DestorySharedMem();
    }
}

//--------------------------------------------------------------------------
// Name        : SMBus_CreateSharedMem
// Description : 建立共享記憶體
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
static inline BOOL SMBus_CreateSharedMem (void)
{
	if( gSMBusMemPtr != NULL && gSMBusMapObject > 0 )
    {
        return TRUE;
    }
    //===========================================================//
    key_t key = (key_t)dSharedOemKey;
    long page_size = sysconf(_SC_PAGESIZE);
    int data_size = dSharedMemSize;
    kprintf("[SMBus Info] key= %d \n", key);
    printf("[SMBus Info] Befort Share Memory cerate : data size: %d, page size: %ld\n", data_size, page_size);

    // 1. create shared memory
    //    shmflag：使用IPC_CREAT時，若沒有shared memory object則建立一個，若有則回傳shared memory id
    //    0644->即用户具有读写权限，组用户和其它用户具有只读权限；
    gSMBusMapObject = shmget( key, data_size, (0644 | IPC_CREAT) );

    if( gSMBusMapObject == -1 )
    {
        perror("shmget failed\n");
        return FALSE;
    }

    printf("[SMBus Info] 1. shmget ,gSMBusMapObject = %d \n", gSMBusMapObject);

    //===========================================================//
    // 2. attach shared memory
    gSMBusMemPtr = (sBusMem *)shmat( gSMBusMapObject, NULL, 0 );

    if( gSMBusMemPtr == (void *)-1 )
    {
        printf("[SMBus Info] 2. attach shared (shmat) failed \n");
        return FALSE;
    }

	printf("[SMBus Info] 2. attach shared (shmat) success \n");

	//===========================================================//
	// 3. write data to shared memory
	if( gSMBusMemPtr->shmid != gSMBusMapObject )
	{
	    printf("[SMBus Info] It's first time create memory \n");

        memset( gSMBusMemPtr, 0, dSharedMemSize );

        gSMBusMemPtr->shmid = gSMBusMapObject;

        printf("[SMBus Info] 3. First time write shared memory , gSMBusMemPtr->shmid = %d \n", gSMBusMemPtr->shmid);

        for( int i = 0; i < 4; i++ )
            gSMBusMemPtr->UserOffset[i] = 0;

        gSMBusMemPtr->TempOffset = sizeof(sBusMem);
    }

    printf("[SMBus Info] done !\n");
    return TRUE;
}

//--------------------------------------------------------------------------
// Name        : SMBus_DestorySharedMem
// Description : 刪除共享記憶體
// Arguments   :
// Return      : None
//---------------------------------------------------------------------------
static inline void SMBus_DestorySharedMem(void)
{
    int nInstCount = (-1);

    if( gSMBusMemPtr != NULL )
    {
        nInstCount = gSMBusMemPtr->InstCount;

        if( gnLocalInstCount == 0 )
        {
            printf("[SMBus Info] Destory memory , access memory count = %d \n", nInstCount);

            // 4. Only detach shared memory, and shared memory still exist.
            if( shmdt(gSMBusMemPtr) == -1 )
            {
                printf("[SMBus Info] Destory memory (shmdt) failed \n");
                exit(EXIT_FAILURE);
            }

            else
            {
                printf("[SMBus Info] Destory memory (shmdt) success \n");
                gSMBusMemPtr = NULL;
            }
        }
    }

    //============================//
    if( gSMBusMapObject > 0 )
    {
        //if no one access share memory , delete share memory
        if( gnLocalInstCount == 0 )
        {
            if( nInstCount == 0 )
            {
                // 5. delete shared memory
                if( shmctl( gSMBusMapObject, IPC_RMID, 0 ) == -1 )
                {
                    printf("[SMBus Info] Delete shared memory (shmctl) failed \n");
                    exit(EXIT_FAILURE);
                }

                else
                    printf("[SMBus Info] Delete shared memory (shmctl) success \n");
            }

            gSMBusMapObject = 0;
        }
    }
}


//--------------------------------------------------------------------------
// Name        : SMBus_Clear
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void SMBus_Clear() //Need to planing for Multi-Controller Architecture leon 2011/5/10
{
    if( gSMBusMemPtr == NULL )
        return;

    //==========================//
    BYTE IoState = 0x00;

    do{
        switch(gSMBusMemPtr->DeviceID)
        {
        case VIA_VX900_BUS_CTRL_DEVICE_ID:
            SMBusIoWrite( SMBHSTSTS, 0xDF );//For VX900 SMBus HST_STS Clear Code
            break;

        default:
            SMBusIoWrite( SMBHSTSTS, 0xFF );//For Normal SMBus HST_STS Clear Code
            break;
        }
        usleep(1);

        IoState = SMBusIoRead(SMBHSTSTS);
        usleep(1);

        IoState = (IoState & 0x01);

    } while(IoState != 0);

    SMBusIoWrite( SMBHSTDAT0, 0x00 );
}

//--------------------------------------------------------------------------
// Name        : SMBus_Wait
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
int SMBus_Wait()
{
    int	timeout = SMBUS_TIMEOUT;
    DWORD dwValue;

    while(timeout--)
    {
        // I/O Delay
        usleep(1);

        // Read Host Status Register
        dwValue = SMBusIoRead(SMBHSTSTS) & 0x00FF;


        if( dwValue & SMBHSTSTS_INTR )
        {
            //printf("SMBus Action Completion! %x\n",dwValue);
            return SMBUS_OK;
        }

        //=================//
        dwValue &= (SMBHSTSTS_FAILED | SMBHSTSTS_COLLISION | SMBHSTSTS_ERROR);

        if(dwValue)
            return (dwValue);
    }

    return SMBUS_BUSY;
}

//--------------------------------------------------------------------------
// Name        : SMBus_Busy
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_Busy()
{
    int nRet = false;

    if( (SMBusIoRead(SMBHSTSTS) & SMBHSTSTS_BUSY) == 1 )
        nRet = true;

    return nRet;
}

//--------------------------------------------------------------------------
// Name        : SMBus_CheckDevice
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_CheckDevice (BYTE byteDeviceAddress)
{
    if( gSMBusMemPtr == NULL )
        return false;

    //==========================//
    int nRet = false;

    pthread_mutex_lock(&gSMBusMemPtr->LockSection);

    // Clear Status First !
    SMBus_Clear();

    if( SMBus_Busy() == false )
    {
        SMBusIoWrite( SMBHSTADD, byteDeviceAddress & (~1) );
        SMBusIoWrite( SMBHSTCNT, (SMBHSTCNT_START | SMBHSTCNT_QUICK) );

        nRet = (SMBus_Wait() == SMBUS_OK);
    }

    pthread_mutex_unlock(&gSMBusMemPtr->LockSection);

    return nRet;
}
//20210304 add by Nico ↓↓↓
//--------------------------------------------------------------------------
// Name        : SMBus_CheckDevice
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_CheckChip(BYTE byteSlave, WORD deviceID, BYTE CHIP_ID_REGISTER2, BYTE CHIP_ID_REGISTER1)
{
    BYTE tempID = 0x0;
	WORD checkID = 0x0;

	SMBus_ReadByte(byteSlave, CHIP_ID_REGISTER2, &tempID);
	checkID = (WORD)tempID;
	SMBus_ReadByte(byteSlave, CHIP_ID_REGISTER1, &tempID);
	checkID = (checkID << 8) | (WORD)tempID;

	if (checkID == deviceID)
	{
		return true;
	}
	return false;
}
//20210304 add by Nico ↑↑↑
//--------------------------------------------------------------------------
// Name        : SMBus_WriteByte
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
int SMBus_WriteByte (BYTE byteSlave,BYTE pCmd,BYTE  pByte)
{
    if( gSMBusMemPtr == NULL )
        return false;

    //==========================//
    int nRet = false;
    int err=1;
    int errcount=0;
    struct tm *tmp;
    char buf[64];
    const long BILLION = 1000000000;
    //pthread_mutex_lock(&gSMBusMemPtr->LockSection);
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    //printf("time_out.tv_sec=%ld ,time_out.tv_nsec= %ld\n",tout.tv_sec,tout.tv_nsec);
    //printf("current time is %s\n", buf); 
    //tout.tv_sec += 5;
	
    while(err)
    {	
    	clock_gettime(CLOCK_REALTIME, &tout);
	//tout.tv_nsec += 5*1000*1000;
	tout.tv_nsec += 500*1000;
    	if (tout.tv_nsec >= BILLION)
	{
		tout.tv_sec += tout.tv_nsec / BILLION;
		tout.tv_nsec %= BILLION;
	}
    	err = pthread_mutex_timedlock(&gSMBusMemPtr->LockSection, &tout);
    	
    	if(err== 0)
    	{
    		//clock_gettime(CLOCK_REALTIME, &tout);
	    	//printf("time_out.tv_sec=%ld ,time_out.tv_nsec= %ld\n",tout.tv_sec,tout.tv_nsec);
		//printf("errcount = %d \n",errcount);
    		break;
    	}
	//printf("///////////////////////////////////////////////////////////////////////////////////////////\n");	
	//printf("////////////////SMBus_WriteByte pthread_mutex_timedlock error = %d/////////////////////////\n",err);
	//printf("///////////////////////////////////////////////////////////////////////////////////////////\n");    	
	errcount++;
    }
    SMBus_Clear();
    if( SMBus_Busy() == false )
    {
        SMBusIoWrite( SMBHSTADD  , byteSlave & (~1) );
        SMBusIoWrite( SMBHSTCMD  , pCmd );
        SMBusIoWrite( SMBHSTDAT0 , pByte );
        SMBusIoWrite( SMBHSTCNT  , (SMBHSTCNT_START | SMBHSTCNT_BYTE) );
        nRet = (SMBus_Wait() == SMBUS_OK);
    }
    pthread_mutex_unlock(&gSMBusMemPtr->LockSection);

    return nRet;
}

//--------------------------------------------------------------------------
// Name        : SMBus_ReadByte
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
int SMBus_ReadByte(BYTE byteSlave, BYTE pCmd, BYTE *pByte)
{
    if( gSMBusMemPtr == NULL )
    {
        return false;
    }
    //==========================//
    int nRet = false;
    int err=1;
    int errcount=0;
	struct tm *tmp;
	char buf[64];
	const long BILLION = 1000000000;
  	
    //pthread_mutex_lock(&gSMBusMemPtr->LockSection);
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    //printf("time_out.tv_sec=%ld ,time_out.tv_nsec= %ld\n",tout.tv_sec,tout.tv_nsec);
    //printf("current time is %s\n", buf);
    //tout.tv_sec += 5;
    
    while(err)
    {
    	clock_gettime(CLOCK_REALTIME, &tout);
    	//tout.tv_nsec += 5*1000*1000;
    	tout.tv_nsec += 500*1000;
    	err = pthread_mutex_timedlock(&gSMBusMemPtr->LockSection, &tout);
    	
    	if(err== 0)
    	{
    		/*clock_gettime(CLOCK_REALTIME, &tout);
    		if (tout.tv_nsec >= BILLION)
		{
			tout.tv_sec += tout.tv_nsec / BILLION;
			tout.tv_nsec %= BILLION;
		}*/
   	    	//printf("time_out.tv_sec=%ld ,time_out.tv_nsec= %ld\n",tout.tv_sec,tout.tv_nsec);
   	    	//printf("errcount = %d \n",errcount);
		break;
    	}
	//printf("////////////////////////////////////////////////////////////////////////////////////////////\n");	
	//printf("////////////////SMBus_ReadByte pthread_mutex_timedlock error = %d///////////////////////////\n",err);
	//printf("////////////////////////////////////////////////////////////////////////////////////////////\n");    	    	
	errcount++;
    }  

//usleep(5000000);
    SMBus_Clear();
    if( SMBus_Busy() == false )
    {
        SMBusIoWrite( SMBHSTADD  , (byteSlave | 0x01) );
        SMBusIoWrite( SMBHSTCMD  , pCmd );
        SMBusIoWrite( SMBHSTCNT  , (SMBHSTCNT_START | SMBHSTCNT_BYTE) );

        if( SMBus_Wait() == SMBUS_OK )
        {
            *pByte = (BYTE)SMBusIoRead(SMBHSTDAT0) & 0xFF;

            nRet = true;
        }
    }
    pthread_mutex_unlock(&gSMBusMemPtr->LockSection);

	return nRet;
}

//--------------------------------------------------------------------------
// Name        : SMBus_WriteWord
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_WriteWord(BYTE tSlaveAddr , BYTE tCmd , WORD tWord)
{
    if( gSMBusMemPtr == NULL )
        return false;

    //==========================//
    int nRet = false;

    pthread_mutex_lock(&gSMBusMemPtr->LockSection);

    SMBus_Clear();

    if( SMBus_Busy() == false )
    {
        SMBusIoWrite( SMBHSTADD  , (tSlaveAddr & 0xFE) );
        SMBusIoWrite( SMBHSTCMD  , tCmd );
        SMBusIoWrite( SMBHSTDAT0 , (BYTE)(tWord & 0xFF) );
        SMBusIoWrite( SMBHSTDAT1 , (BYTE)(tWord >> 8) );
        SMBusIoWrite( SMBHSTCNT  , (SMBHSTCNT_START | SMBHSTCNT_WORD) );

        nRet = (SMBus_Wait() == SMBUS_OK);
    }

    pthread_mutex_unlock(&gSMBusMemPtr->LockSection);

    return nRet;
}

//--------------------------------------------------------------------------
// Name        : SMBus_ReadWord
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_ReadWord(BYTE byteSlave , BYTE pCmd , WORD *pWord)
{
    if( gSMBusMemPtr == NULL )
        return false;

    //==========================//
    int nRet = false;

    pthread_mutex_lock(&gSMBusMemPtr->LockSection);

    SMBus_Clear();

    if( SMBus_Busy() == false )
    {
        BYTE high, low;

        SMBusIoWrite( SMBHSTADD  , (byteSlave | 0x01) );
        SMBusIoWrite( SMBHSTCMD  , pCmd );

//        SMBusIoWrite(SMBHSTCNT  , SMBHSTCNT_WORD);
//        ret = SMBus_Wait();

        SMBusIoWrite( SMBHSTCNT  , (SMBHSTCNT_START | SMBHSTCNT_WORD) );

        if( SMBus_Wait() == SMBUS_OK )
        {
            low = SMBusIoRead(SMBHSTDAT0);
            high = SMBusIoRead(SMBHSTDAT1);
            *pWord = ((high & 0xff) << 8) | (low & 0xff);

            //printf("[INFO] SMBus read WORD , pWord = %x \n", *pWord);
            nRet = true;
        }
    }

    pthread_mutex_unlock(&gSMBusMemPtr->LockSection);

    return nRet;
}

//--------------------------------------------------------------------------
// Name        : SMBus_WriteBlock
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_WriteBlock(BYTE tSlaveAddr, BYTE tCmd, BYTE *tBlock)
{
    if( gSMBusMemPtr == NULL )
        return false;

    //==========================//
    int nRet = false;

    pthread_mutex_lock(&gSMBusMemPtr->LockSection);

    SMBus_Clear();

    if( SMBus_Busy() == false )
    {
        if( gSMBusMemPtr->VendorID == dVendorID_Intel )
        {
            //Set SMBAUXCTL_E32B
            BYTE u8val = SMBusIoRead(SMBAUXCTL);
            SMBusIoWrite( SMBAUXCTL, (u8val | SMBAUXCTL_E32B) );

            if( SMBusIoRead(SMBAUXCTL) & SMBAUXCTL_E32B )
            {
                SMBusIoWrite( SMBHSTADD, (tSlaveAddr & 0xFE) );
                SMBusIoWrite( SMBHSTCMD, tCmd );

                SMBusIoRead(SMBHSTCNT);  // Reset SMBBLKDAT

                SMBusIoWrite (SMBHSTDAT0, tBlock[0] );

                for( int i = 1; i <= tBlock[0]; i++ )
                    SMBusIoWrite( SMBBLKDAT, tBlock[i] );

                SMBusIoWrite( SMBHSTCNT, (SMBHSTCNT_START | SMBHSTCNT_BLOCK) );

                nRet = (SMBus_Wait() == SMBUS_OK); // Set return value

                //Unset SMBAUXCTL_E32B
                SMBusIoWrite( SMBAUXCTL, u8val );
            }
        }

        else if( gSMBusMemPtr->VendorID == dVendorID_VIA )
        {
            SMBusIoWrite( SMBHSTADD, (tSlaveAddr & 0xFE) );
            SMBusIoWrite( SMBHSTCMD, tCmd );

            SMBusIoWrite( SMBHSTDAT0, tBlock[0] );

            SMBusIoRead(SMBHSTCNT);               // Reset SMBBLKDAT

            for( int i = 1; i <= tBlock[0]; i++)
                SMBusIoWrite( SMBBLKDAT, tBlock[i] );

            SMBusIoWrite( SMBHSTCNT, (SMBHSTCNT_START | SMBHSTCNT_BLOCK) );

            nRet = (SMBus_Wait() == SMBUS_OK);     // Set return value
        }
    }

    pthread_mutex_unlock(&gSMBusMemPtr->LockSection);

    return nRet;
}

//--------------------------------------------------------------------------
// Name        : SMBus_ReadBlock
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
bool SMBus_ReadBlock(BYTE tSlaveAddr, BYTE tCmd, BYTE *tBlock)
{
    if( gSMBusMemPtr == NULL )
        return false;

    //==========================//
    int nRet = false;

    pthread_mutex_lock(&gSMBusMemPtr->LockSection);

    SMBus_Clear();

    if( SMBus_Busy() == false )
    {
        int nStartRd = false;
        BYTE u8val;

        if( gSMBusMemPtr->VendorID == dVendorID_Intel )
        {
            //Set SMBAUXCTL_E32B
            u8val = SMBusIoRead(SMBAUXCTL);
            SMBusIoWrite( SMBAUXCTL, (u8val | SMBAUXCTL_E32B) );

            if( SMBusIoRead(SMBAUXCTL) & SMBAUXCTL_E32B )
                nStartRd = true;
        }

        else if( gSMBusMemPtr->VendorID == dVendorID_VIA )
            nStartRd = true;

        //==========================//
        if( nStartRd == true )
        {
            SMBusIoWrite( SMBHSTADD, (tSlaveAddr | 0x01) );
            SMBusIoWrite( SMBHSTCMD, tCmd);
            SMBusIoWrite( SMBHSTCNT, (SMBHSTCNT_START | SMBHSTCNT_BLOCK) );

            if( SMBus_Wait() == SMBUS_OK )
            {
                tBlock[0] = SMBusIoRead(SMBHSTDAT0);

                if( tBlock[0] > I2C_SMBUS_BLOCK_MAX )
                    tBlock[0] = I2C_SMBUS_BLOCK_MAX;

                SMBusIoRead(SMBHSTCNT);            // Reset SMBBLKDAT

                for( int i = 1; i <= tBlock[0]; i++ )
                    tBlock[i] = SMBusIoRead(SMBBLKDAT);

                nRet = true;
            }
        }

        //==========================//
        //Unset SMBAUXCTL_E32B
        if( gSMBusMemPtr->VendorID == dVendorID_Intel )
            SMBusIoWrite( SMBAUXCTL, u8val );
    }

    pthread_mutex_unlock(&gSMBusMemPtr->LockSection);

    return nRet;
}
//20210309 add by Nico ↓↓↓
//--------------------------------------------------------------------------
// Name        : AMD PMIO Read
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
DWORD AMD_PMIO_Read(DWORD dwIndexVal)
{
	DWORD dwAddrVal;
	//SetPortVal(AMD_PMIO_INDEX, dwIndexVal, size_t);
	//GetPortVal(AMD_PMIO_DATA, &dwAddrVal, size_t);
    outl(dwIndexVal,AMD_PMIO_INDEX);
    dwAddrVal=inl(AMD_PMIO_DATA);

	return dwAddrVal;
}
//--------------------------------------------------------------------------
// Name        : AMD PMIO Write
// Description :
// Arguments   :
// Return      : Success return true
//---------------------------------------------------------------------------
void AMD_PMIO_Write(DWORD dwIndexVal, DWORD dwDataVal)
{
    outl(dwIndexVal,AMD_PMIO_INDEX);
    outl(dwDataVal,AMD_PMIO_DATA);
    //::SetPortVal(AMD_PMIO_INDEX, dwDataVal, size_t);
    //::SetPortVal(AMD_PMIO_DATA, dwDataVal, size_t);
}
//20210309 add by Nico ↑↑↑

