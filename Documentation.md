## Low Level API

Following libraries from `sys/io.h` are being used:
```C
#include <sys/io.h>
unsigned char inb(unsigned short int port);
unsigned char inb_p(unsigned short int port);
unsigned short int inw(unsigned short int port);
unsigned short int inw_p(unsigned short int port);
unsigned int inl(unsigned short int port);
unsigned int inl_p(unsigned short int port);
void outb(unsigned char value, unsigned short int port);
void outb_p(unsigned char value, unsigned short int port);
void outw(unsigned short int value, unsigned short int port);
void outw_p(unsigned short int value, unsigned short int port);
void outl(unsigned int value, unsigned short int port);
void outl_p(unsigned int value, unsigned short int port);
void insb(unsigned short int port, void *addr, unsigned long int count);
void insw(unsigned short int port, void *addr, unsigned long int count);
void insl(unsigned short int port, void *addr, unsigned long int count);
void outsb(unsigned short int port, const void *addr, unsigned long int count);
void outsw(unsigned short int port, const void *addr, unsigned long int count);
void outsl(unsigned short int port, const void *addr, unsigned long int count);
```

## What happens there?

* SMBus Initialising (SMBus.c:310)
  * Reserve Shared Memory
> We will try to skip the usage of shared memory
  * SMBusIoWrite(SMBAUXCTL, SMBusIoRead(SMBAUXCTL) & ~(SMBAUXCTL_CRC | SMBAUXCTL_E32B));
* F75111 Initialising (main.c:297)
  * `SMBus_CheckChip(m_F75111.bAddress, F75111_DEVICE_ID, F75111_CHIP_ID_REGISTER_2, F75111_CHIP_ID_REGISTER_1);`
  * `SMBus_ReadByte(m_F75111.bAddress, GPIO1X_OUTPUT_DATA, &byteGPIO1X);`
  * gpio14-gpio17 set output: `SMBus_WriteByte(m_F75111.bAddress, GPIO1X_CONTROL_MODE, (byteGPIO1X & 0x0f) | 0xf0);`
  * gpio14-gpio17 set output driving: `SMBus_WriteByte(m_F75111.bAddress, GPIO1X_OUTPUT_DRIVING, (byteGPIO1X & 0x0f) | 0xf0);`
  * gpio20-gpio27 set output: `SMBus_WriteByte(m_F75111.bAddress, GPIO2X_CONTROL_MODE, 0xFF);`
  * gpio20-gpio27 set output driving: `SMBus_WriteByte(m_F75111.bAddress, GPIO2X_OUTPUT_DRIVING, 0xFF);`
  * gpio30-gpio33 set output: `SMBus_WriteByte(m_F75111.bAddress, GPIO3X_CONTROL_MODE, 0x0F);`
  * gpio30-gpio33 set output driving: `SMBus_WriteByte(m_F75111.bAddress, GPIO3X_OUTPUT_DRIVING, 0x0F);`
  * `SMBus_WriteByte(m_F75111.bAddress,F75111_CONFIGURATION,0x03);`
  * `SMBus_WriteByte(m_F75111.bAddress, 0x06, 0x04);`

> The weird part of the LexSystems implementation of SMBus is, that SMBus has no Address+Offset-Addressing:
> https://docs.kernel.org/i2c/smbus-protocol.html

### `SMBusIoWrite`
Write one byte to SMBus address at specified offset
```C
outb(byteData, (SMBusAddr + byteOffset));
```

### `SMBusIORead`
Storing a double word from a returned byte and filtering only to get the LSB. Seems unnecessary:
```C
DWORD dwAddrVal = inb((SMBusAddr + byteOffset));
usleep(10);
return (BYTE)(dwAddrVal & 0x0FF);
```
can IMO be written as
```C
return inb(SMBusAddr + byteOffset);
```

### `SMBus_WriteByte`
Locked section to write a byte (`pByte`) via command (`pCmd`) to a specified address (`byteSlave`)
```C
SMBus_Clear();
if (SMBus_Busy() == false)
{
    SMBusIoWrite(SMBHSTADD, byteSlave & ~0x01);
    SMBusIoWrite(SMBHSTCMD, pCmd);
    SMBusIoWrite(SMBHSTDAT0, pByte);
    SMBusIoWrite(SMBHSTCNT, (SMBHSTCNT_START | SMBHSTCNT_BYTE));
    nRet = (SMBus_Wait() == SMBUS_OK);
}
```

### `SMBus_ReadByte`
Locked seciont to read a byte via command (`pCmd`) from a specified address (`byteSlave`)
```C
SMBus_Clear();
if (SMBus_Busy() == false)
{
  SMBusIoWrite(SMBHSTADD, (byteSlave | 0x01));
  SMBusIoWrite(SMBHSTCMD, pCmd);
  SMBusIoWrite(SMBHSTCNT, (SMBHSTCNT_START | SMBHSTCNT_BYTE));
  
  if (SMBus_Wait() == SMBUS_OK)
    return SMBusIoRead(SMBHSTDAT0);
}
return 0x0;
```
### `SMBus_Busy`
Checks if SMBus is not available
```C
SMBusIoRead(SMBHSTSTS) & SMBHSTSTS_BUSY
```

### `SMBus_Wait`

```C
// Shortened original code:
int	timeout = SMBUS_TIMEOUT;
DWORD dwValue;
while(timeout--)
{
    usleep(1);
    dwValue = SMBusIoRead(SMBHSTSTS) & 0x00FF;
    if( dwValue & SMBHSTSTS_INTR )
        return SMBUS_OK;
    dwValue &= (SMBHSTSTS_FAILED | SMBHSTSTS_COLLISION | SMBHSTSTS_ERROR);
    if(dwValue)
        return dwValue;
}
return SMBUS_BUSY;
```

Optimizing the code, we can simplify it:
```C
int	limit = SMBUS_TIMEOUT;
BYTE value;
while(--limit)
{
    udelay(1);
    value = SMBusIoRead(SMBHSTSTS);
    if(value & SMBHSTSTS_INTR)
        return SMBUS_OK;
    value &= (SMBHSTSTS_FAILED | SMBHSTSTS_COLLISION | SMBHSTSTS_ERROR);
    if(value)
        return dwValue;
}
return SMBUS_BUSY;
```

### `SMBus_CheckChip`
Compare the chip hardware ID WORD with an arbitrary one (`deviceID`)
```C
WORD tempID = 0x0;
WORD checkID = 0x0;
SMBus_ReadByte(byteSlave, CHIP_ID_REGISTER2, &tempID);
checkID = tempID << 8;
SMBus_ReadByte(byteSlave, CHIP_ID_REGISTER1, &tempID);
checkID |= tempID;
return (checkID == deviceID);
```

### `SMBus_Clear`
Clears any processes from the SMBus
```C
BYTE IoState = 0x00;
do {
    SMBusIoWrite(SMBHSTSTS, 0xFF);
    usleep(1);
    IoState = SMBusIoRead(SMBHSTSTS);
    usleep(1);
} while((IoState & 0x01) != 0);
SMBusIoWrite(SMBHSTDAT0, 0x00);
```
IMO, the clear command should only be sent once and waiting should be done up to a max (e.g. 10 times):
```C
SMBusIoWrite(SMBHSTSTS, 0xFF);
udelay(1);
BYTE IoState;
uint8 limit = 10;
do {
    udelay(1);
    IoState = SMBusIoRead(SMBHSTSTS);
} while(IoState & 0x01 || (--limit > 0));
if (IoState & 0x01)
    SMBusIoWrite(SMBHSTDAT0, 0x00);
```

## F75111 Initialising
As the initialization of the chip is really a blackbox, I disassembled it down to the SMBUS calls.
We have the following bases:
- SMBus base address is `3040`; we are calling it `base`
- We have the following predefined offsets:
  - `SMBHSTCNT`	= 0x02	// SMBus Control register
  - `SMBHSTCMD` = 0x03	// SMBus Command register
  - `SMBHSTADD` = 0x04	// SMBus Address register
  - `SMBHSTDAT0` = 0x05 // SMBus Data 0 register
  - `SMBHSTDAT1` = 0x06 // SMBus Data 1 register

The call tree looks like follows:
* `F75111_Init()`
  * `SMBus_CheckChip(base, F75111_DEVICE_ID=0x0003, F75111_CHIP_ID_REGISTER_2=0x5B, F75111_CHIP_ID_REGISTER_1=0x5A)`
    * `SMBus_ReadByte(base, CHIP_ID_REGISTER2=0x5B, &result)`
      * `SMBus_Clear()`
        * `SMBusIoWrite(base, 0xFF)`
        * `SMBusIoRead(base)`
        * `SMBusIoWrite(base + SMBHSTDAT0, 0xFF)`
      * `SMBus_Busy()`
        * `SMBusIoRead(base)` (Return if `0x01` bit is set)
      * `SMBusIoWrite(base + SMBHSTADD, F75111_INTERNAL_ADDR=0x9C | 0x01)`
      * `SMBusIoWrite(base + SMBHSTCMD, CHIP_ID_REGISTER2=0x5B)`
      * `SMBusIoWrite(base + SMBHSTCNT, SMBHSTCNT_BYTE=0x08 | SMBHSTCNT_START=0x40)` (=0x48)
      * Check if `SMBus_Wait()` == SMBUS_OK=0x0
        * `SMBusIoRead(base)`
        * if result has `SMBHSTSTS_INTR=0x02` bit set, return SMBUS_OK=0x0
        * elif result has one of (SMBHSTSTS_FAILED=0x10 | SMBHSTSTS_COLLISION=0x08 | SMBHSTSTS_ERROR=0x04), return result
        * else repeat
      * Read query result from result register: `SMBusIoRead(base + SMBHSTDAT0)`

## Lessons learned
* Delaying should not be done with the scheduler [according to Linus](https://github.com/torvalds/linux/blob/a351e9b9fc24e982ec2f0e76379a49826036da12/Documentation/timers/timers-howto.txt)

Bad:
```C
#include <sys/time.h>
usleep(1);
```

Good:
```C
#include <linux/delay.h>
udelay(1);
```