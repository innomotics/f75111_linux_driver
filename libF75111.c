#include "SMBus.h"
#include "libF75111.h"
#include <unistd.h>

extern F75111_Address m_F75111;

/*
bool Led_Stop(struct innomotics_ipc_led *led)
{
    struct innomotics_ipc_led cur = innomotics_ipc_leds_f75111;
    while (cur.num > 0) {
        if (cur.num == led->num) {
            F75111_SetDigitalOutput_Pin(cur.num,false);
        }
        cur++;
    }
}
*/

bool F75111_Init()
{
    if (SMBus_CheckChip(m_F75111.bAddress, F75111_DEVICE_ID, F75111_CHIP_ID_REGISTER_2, F75111_CHIP_ID_REGISTER_1))
    {
        BYTE byteGPIO1X = 0;

        SMBus_ReadByte(m_F75111.bAddress,GPIO1X_OUTPUT_DATA,&byteGPIO1X) ;
        SMBus_WriteByte(m_F75111.bAddress, GPIO1X_CONTROL_MODE,(byteGPIO1X & 0x0f) | 0xf0);		//gpio14-gpio17 set output
        SMBus_WriteByte(m_F75111.bAddress, GPIO1X_OUTPUT_DRIVING, (byteGPIO1X & 0x0f)|0xf0);	//gpio14-gpio17 set output driving

        SMBus_WriteByte(m_F75111.bAddress, GPIO2X_CONTROL_MODE, 0xFF);							//gpio20-gpio27 set output
        SMBus_WriteByte(m_F75111.bAddress, GPIO2X_OUTPUT_DRIVING, 0xFF);						//gpio20-gpio27 set output driving

        SMBus_WriteByte(m_F75111.bAddress, GPIO3X_CONTROL_MODE, 0x0F);							//gpio30-gpio33 set output
        SMBus_WriteByte(m_F75111.bAddress, GPIO3X_OUTPUT_DRIVING, 0x0F);						//gpio30-gpio33 set output driving

        SMBus_WriteByte(m_F75111.bAddress,F75111_CONFIGURATION,0x03);
        SMBus_WriteByte(m_F75111.bAddress, 0x06, 0x04);

        return true;
    }
    return false;
}

bool F75111_SetDigitalOutput_Pin(BYTE pin_number,bool pin_status)
{
    BYTE tmp, a=0x1;
    BYTE byteGPIO1X = 0;
    BYTE byteGPIO2X = 0;
    BYTE byteGPIO3X = 0;
    BYTE byteData = 0;

    if((pin_number >= 0 ) && (pin_number <= 7))
    {
        //tmp=F75111_GetDigitalInput();
        SMBus_ReadByte(m_F75111.bAddress, GPIO2X_INPUT_DATA, &byteGPIO2X);
        byteData = (byteGPIO2X & 0x01 )? byteData + 0x01 : byteData;
        byteData = (byteGPIO2X & 0x02 )? byteData + 0x02 : byteData;
        byteData = (byteGPIO2X & 0x04 )? byteData + 0x04 : byteData;
        byteData = (byteGPIO2X & 0x80 )? byteData + 0x08 : byteData;

        byteData = (byteGPIO2X & 0x40 )? byteData + 0x10 : byteData;
        byteData = (byteGPIO2X & 0x20 )? byteData + 0x20 : byteData;
        byteData = (byteGPIO2X & 0x10 )? byteData + 0x40 : byteData;
        byteData = (byteGPIO2X & 0x08 )? byteData + 0x80 : byteData;

        tmp=byteData;
        if(pin_status)
        {
            a=a<< (pin_number-1);
            tmp=tmp | a ;
            F75111_SetDigitalOutput(tmp);
        }
        else
        {
            a=a<< (pin_number-1);
            tmp=tmp & ~a;
            F75111_SetDigitalOutput(tmp);
        }
    }
    else if ((pin_number >= 8 ) && (pin_number <= 15))
    {
        SMBus_ReadByte(m_F75111.bAddress, GPIO2X_INPUT_DATA, &byteGPIO1X);
        SMBus_ReadByte(m_F75111.bAddress, GPIO2X_INPUT_DATA, &byteGPIO3X);

        byteData = (byteGPIO1X & 0x10 )? byteData + 0x01 : byteData;
        byteData = (byteGPIO1X & 0x80 )? byteData + 0x02 : byteData;
        byteData = (byteGPIO1X & 0x40 )? byteData + 0x04 : byteData;
        byteData = (byteGPIO3X & 0x01 )? byteData + 0x08 : byteData;

        byteData = (byteGPIO3X & 0x02 )? byteData + 0x10 : byteData;
        byteData = (byteGPIO3X & 0x04 )? byteData + 0x20 : byteData;
        byteData = (byteGPIO3X & 0x08 )? byteData + 0x40 : byteData;
        byteData = (byteGPIO1X & 0x20 )? byteData + 0x80 : byteData;


        tmp=byteData;
        //printf("tmp = 0x%x \n",tmp);
        if(pin_status)
        {
            a=a<< (pin_number-9);
            tmp=tmp | a ;
            //printf("tmp = 0x%x \n",tmp);
            F75111_SetDigitalOutput_2(tmp);
        }
        else
        {
            a=a<< (pin_number-9);
            tmp=tmp & ~a;
            //printf("tmp = 0x%x \n",tmp);
            F75111_SetDigitalOutput_2(tmp);
        }

    }
    return true;
}

void F75111_SetDigitalOutput(BYTE byteValue)
{
    BYTE byteData = 0;
    BYTE byteData2 = 0;

    byteData = (byteValue & 0x01 )? byteData + 0x01 : byteData;
    byteData = (byteValue & 0x02 )? byteData + 0x02 : byteData;
    byteData = (byteValue & 0x04 )? byteData + 0x04 : byteData;
    byteData = (byteValue & 0x80 )? byteData + 0x08 : byteData;

    byteData = (byteValue & 0x40 )? byteData + 0x10 : byteData;
    byteData = (byteValue & 0x20 )? byteData + 0x20 : byteData;
    byteData = (byteValue & 0x10 )? byteData + 0x40 : byteData;
    byteData = (byteValue & 0x08 )? byteData + 0x80 : byteData;

    SMBus_WriteByte(m_F75111.bAddress,GPIO2X_OUTPUT_DATA,byteData);
    usleep(10);
}

void F75111_SetDigitalOutput_2(BYTE byteValue)
{
    BYTE byteData = 0;
    BYTE byteData2 = 0;

    byteData = (byteValue & 0x01 )? byteData + 0x10 : byteData;
    byteData = (byteValue & 0x02 )? byteData + 0x80 : byteData;
    byteData = (byteValue & 0x04 )? byteData + 0x40 : byteData;
    byteData2 = (byteValue & 0x08 )? byteData2 + 0x01 : byteData2;

    byteData2 = (byteValue & 0x10 )? byteData2 + 0x02 : byteData2;
    byteData2 = (byteValue & 0x20 )? byteData2 + 0x04 : byteData2;
    byteData2 = (byteValue & 0x40 )? byteData2 + 0x08 : byteData2;
    byteData = (byteValue & 0x80 )? byteData + 0x20 : byteData;

    SMBus_WriteByte(m_F75111.bAddress,GPIO1X_OUTPUT_DATA,byteData);
    SMBus_WriteByte(m_F75111.bAddress,GPIO3X_OUTPUT_DATA,byteData2);

    usleep(10);
}


void F75111_SetWDTEnable (BYTE byteTimer)
{
    SMBus_WriteByte(m_F75111.bAddress,WDT_TIMER_RANGE  ,byteTimer);
    usleep(10);
    SMBus_WriteByte(m_F75111.bAddress,WDT_CONFIGURATION,WDT_TIMEOUT_FLAG | WDT_ENABLE | WDT_PULSE | WDT_PSWIDTH_100MS);
}

void F75111_SetWDTDisable ()
{
    SMBus_WriteByte(m_F75111.bAddress,WDT_CONFIGURATION,0x00);
}

