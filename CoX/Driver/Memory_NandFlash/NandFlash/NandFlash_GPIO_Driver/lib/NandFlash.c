//*****************************************************************************
//
//! \file NandFlash.c
//! \brief the NandFlash Driver.
//! \version V0.0.1
//! \date 2/5/2013
//! \author CooCox
//! \copy
//
//! \attention This Basic NAND Flash Driver Doesn't Deal With Bad Block Issue!
//! Bad block management will be added in following version.
//! \attention Since the initial invalid block information is also erasable in
//! most cases, it is impossible to recover the information once it has been erased!
//
//! Copyright (c)  2013, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
//!
//!     * Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     * Neither the name of the <ORGANIZATION> nor the names of its
//! contributors may be used to endorse or promote products derived
//! from this software without specific prior written permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//! THE POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_gpio.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xuart.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "hw_NandFlash.h"
#include "NandFlash.h"

//*****************************************************************************
//
//! \brief NAND Flash IO control macro
//
//*****************************************************************************
#define NF_CLE_SET          xGPIOSPinWrite(NF_CLE_PIN,1)
#define NF_ALE_SET          xGPIOSPinWrite(NF_ALE_PIN,1)
#define NF_NWE_SET          xGPIOSPinWrite(NF_NWE_PIN,1)
#define NF_NRE_SET          xGPIOSPinWrite(NF_NRE_PIN,1)
#define NF_NCE_SET          xGPIOSPinWrite(NF_NCE_PIN,1)
#define NF_NWP_SET          xGPIOSPinWrite(NF_NWP_PIN,1)

#define NF_CLE_CLR          xGPIOSPinWrite(NF_CLE_PIN,0)
#define NF_ALE_CLR          xGPIOSPinWrite(NF_ALE_PIN,0)
#define NF_NWE_CLR          xGPIOSPinWrite(NF_NWE_PIN,0)
#define NF_NRE_CLR          xGPIOSPinWrite(NF_NRE_PIN,0)
#define NF_NCE_CLR          xGPIOSPinWrite(NF_NCE_PIN,0)
#define NF_NWP_CLR          xGPIOSPinWrite(NF_NWP_PIN,0)

#define NF_IS_READY()         xGPIOSPinRead(NF_RNB_PIN)

#ifdef SEQUENCE_PIN_MODE
//
// If the 8 bit data IO pins are at one port in order from GPIO 0~7, 
// enable PARAMODE can increase speed and decrease code size.
//
#define NF_DATA_DIR_IN      xGPIODirModeSet(NF_DATA_PORT, NF_DATA_MASK, xGPIO_DIR_MODE_IN)
#define NF_DATA_DIR_OUT     xGPIODirModeSet(NF_DATA_PORT, NF_DATA_MASK, xGPIO_DIR_MODE_OUT)

#define NF_DATA_OUT(a)      {xGPIOPinWrite(NF_DATA_PORT, a, 1); \
                             xGPIOPinWrite(NF_DATA_PORT, ~(unsigned long)a&NF_DATA_MASK, 0);}
#define NF_DATA_IN()         xGPIOPinRead(NF_DATA_PORT, NF_DATA_MASK)

#else
//
// If the 8 bit data IO pins are separate or not in order from GPIO 0~7, 
// please use the macros below.
//
#define NF_DATA_DIR_IN      do{xGPIOSPinDirModeSet(NF_DB0_PIN, xGPIO_DIR_MODE_IN); \
                            xGPIOSPinDirModeSet(NF_DB1_PIN, xGPIO_DIR_MODE_IN); \
	                        xGPIOSPinDirModeSet(NF_DB2_PIN, xGPIO_DIR_MODE_IN); \
	                        xGPIOSPinDirModeSet(NF_DB3_PIN, xGPIO_DIR_MODE_IN); \
	                        xGPIOSPinDirModeSet(NF_DB4_PIN, xGPIO_DIR_MODE_IN); \
	                        xGPIOSPinDirModeSet(NF_DB5_PIN, xGPIO_DIR_MODE_IN); \
	                        xGPIOSPinDirModeSet(NF_DB6_PIN, xGPIO_DIR_MODE_IN); \
	                        xGPIOSPinDirModeSet(NF_DB7_PIN, xGPIO_DIR_MODE_IN);}while(0)

#define NF_DATA_DIR_OUT     do{xGPIOSPinDirModeSet(NF_DB0_PIN, xGPIO_DIR_MODE_OUT); \
                            xGPIOSPinDirModeSet(NF_DB1_PIN, xGPIO_DIR_MODE_OUT); \
	                        xGPIOSPinDirModeSet(NF_DB2_PIN, xGPIO_DIR_MODE_OUT); \
	                        xGPIOSPinDirModeSet(NF_DB3_PIN, xGPIO_DIR_MODE_OUT); \
	                        xGPIOSPinDirModeSet(NF_DB4_PIN, xGPIO_DIR_MODE_OUT); \
	                        xGPIOSPinDirModeSet(NF_DB5_PIN, xGPIO_DIR_MODE_OUT); \
	                        xGPIOSPinDirModeSet(NF_DB6_PIN, xGPIO_DIR_MODE_OUT); \
	                        xGPIOSPinDirModeSet(NF_DB7_PIN, xGPIO_DIR_MODE_OUT);}while(0)

#define NF_DATA_OUT(a)      do{xGPIOSPinWrite(NF_DB7_PIN,a>>7); \
                            xGPIOSPinWrite(NF_DB6_PIN,a>>6); \
                            xGPIOSPinWrite(NF_DB5_PIN,a>>5); \
                            xGPIOSPinWrite(NF_DB4_PIN,a>>4); \
                            xGPIOSPinWrite(NF_DB3_PIN,a>>3); \
                            xGPIOSPinWrite(NF_DB2_PIN,a>>2); \
                            xGPIOSPinWrite(NF_DB1_PIN,a>>1); \
                            xGPIOSPinWrite(NF_DB0_PIN,a>>0);}while(0)

#define NF_DATA_IN()        ((xGPIOSPinRead(NF_DB7_PIN)<<7) \
                            +(xGPIOSPinRead(NF_DB6_PIN)<<6) \
                            +(xGPIOSPinRead(NF_DB5_PIN)<<5) \
                            +(xGPIOSPinRead(NF_DB4_PIN)<<4) \
                            +(xGPIOSPinRead(NF_DB3_PIN)<<3) \
                            +(xGPIOSPinRead(NF_DB2_PIN)<<2) \
                            +(xGPIOSPinRead(NF_DB1_PIN)<<1) \
                            +(xGPIOSPinRead(NF_DB0_PIN)<<0))
#endif

NandFlashInfo NandInfo;

//*****************************************************************************
//
//! \brief Initialize IO port for NAND Flash
//!
//! \param None
//!
//! This function is to initialize IO port to read/write NAND flash.
//! The default status of the 8 bit data line is initialized to input.
//!
//! \return None.
//
//*****************************************************************************
void NFIOInit(void)
{
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_CLE_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_ALE_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_NWE_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_NRE_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_NCE_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_NWP_PIN));

	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB0_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB1_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB2_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB3_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB4_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB5_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB6_PIN));
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_DB7_PIN));

	xGPIOSPinDirModeSet(NF_CLE_PIN, xGPIO_DIR_MODE_OUT);
	xGPIOSPinDirModeSet(NF_ALE_PIN, xGPIO_DIR_MODE_OUT);
	xGPIOSPinDirModeSet(NF_NWE_PIN, xGPIO_DIR_MODE_OUT);
	xGPIOSPinDirModeSet(NF_NRE_PIN, xGPIO_DIR_MODE_OUT);
	xGPIOSPinDirModeSet(NF_NCE_PIN, xGPIO_DIR_MODE_OUT);
	xGPIOSPinDirModeSet(NF_NWP_PIN, xGPIO_DIR_MODE_OUT);

	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(NF_RNB_PIN));
	xGPIOSPinDirModeSet(NF_RNB_PIN, xGPIO_DIR_MODE_IN);
	//
	// Since Ready/Busy pin is open drain, it needs to pull up to detect the signal.
	//
	xGPIOSPinWrite(NF_RNB_PIN,1);

	//
	// Default data direction is input
	//
	NF_DATA_DIR_IN;

	NF_NCE_SET;
	NF_NWP_SET;
	NF_NWE_SET;
	NF_NRE_SET;
	NF_ALE_CLR;
	NF_CLE_CLR;
}

//*****************************************************************************
//
//! \brief Write one byte to NAND Flash
//!
//! \param ucByte Byte will be written to NAND flash
//!
//! This function is to write one byte to NAND Flash
//!
//! \return None
//
//*****************************************************************************
void NFDataWrite(unsigned char ucByte)
{
	//
	// Set data port direction as output
	//
	NF_DATA_DIR_OUT;
	NF_NWE_CLR;
	NF_DATA_OUT(ucByte);
	NF_NWE_SET;
	//
	// Set data port direction as input
	//
	NF_DATA_DIR_IN;
}

//*****************************************************************************
//
//! \brief Read one byte from NAND Flash
//!
//! \param ucByte
//!
//! This function is to Read one byte from NAND Flash
//!
//! \return Byte which is read out from NAND flash
//
//*****************************************************************************
unsigned char NFDataRead(void)
{
	unsigned char ucRes;

	NF_NRE_CLR;
	ucRes = NF_DATA_IN();
	NF_NRE_SET;
	return ucRes;
}

//*****************************************************************************
//
//! \brief Write command to NAND Flash
//!
//! \param ucCmd
//!
//! This function is to Write command to NAND Flash
//!
//! \return None
//
//*****************************************************************************
void NFCmdWrite(unsigned char ucCmd)
{
	NF_CLE_SET;
	NFDataWrite(ucCmd);
	NF_CLE_CLR;
}

//*****************************************************************************
//
//! \brief Get status after operation
//!
//! \param None
//!
//! This function is to read status after operation to check if the
//! operation is successful.
//!
//! \return status value
//
//*****************************************************************************
unsigned char NFStatusRead(void)
{
	unsigned char ucRes;

	NF_NCE_CLR; //chip enable
	NFCmdWrite(NF_CMD_READSTATUS);
	ucRes = NFDataRead();
	NF_NCE_SET; //chip disable
	return(ucRes);
}

//*****************************************************************************
//
//! \brief Write byte address to NAND Flash
//!
//! \param ulAddr Specifies the byte address
//!
//! This function is to Write byte address, the address don't include spare
//! area. If you want to set address to spare area, you should use
//! NFWriteColumnAddr() defined below.
//!
//! \return None
//
//*****************************************************************************
void NFWriteByteAddr(unsigned long ulAddr)
{
	unsigned char ucAddrtmp;
	unsigned short usShift;

	//
	// Address latch enable
	//
	NF_ALE_SET;

	//
	// 1st column address
	//
	NFDataWrite((unsigned char)ulAddr);
#if(NF_PAGE_SIZE > 512)  // big page NAND flash
	{
		ucAddrtmp = (unsigned char)(ulAddr >> 8);
		ucAddrtmp &= ((NF_PAGE_SIZE - 1) >> 8);
		//
		// 2nd column address
		//
		NFDataWrite(ucAddrtmp);
		usShift = NF_PAGE_SIZE - 1;
		while(usShift&1)
		{
			ulAddr >>= 1;
			usShift >>= 1;
		}
	}
#else // small page NAND flash
	ulAddr >>= 9;
#endif

	//
	// 1st row address
	//
	NFDataWrite((unsigned char)ulAddr);

#if(NF_DEVICE_SIZE / NF_PAGE_SIZE > 0x100)
	//
	// 2nd row address
	//
	ulAddr >>= 8;
	NFDataWrite((unsigned char)ulAddr);
#endif

#if(NF_DEVICE_SIZE / NF_PAGE_SIZE > 0x10000)
	//
	// 3rd row address
	//
	ulAddr >>= 8;
	NFDataWrite((unsigned char)ulAddr);
#endif

	NF_ALE_CLR;
}

//*****************************************************************************
//
//! \brief Write column address to NAND Flash
//!
//! \param ulColAddr Specifies the column address
//!
//! This function is to set column address(byte offset address in a page).
//!
//! \return None
//
//*****************************************************************************
void NFWriteColumnAddr(unsigned long ulColAddr)
{
	NF_ALE_SET;

	NFDataWrite((unsigned char)ulColAddr);

#if(NF_PAGE_SIZE > 512)
	ulColAddr >>= 8;
	NFDataWrite((unsigned char)ulColAddr);
#endif

	NF_ALE_CLR;
}

//*****************************************************************************
//
//! \brief Write row address to NAND Flash
//!
//! \param ulRowAddr Specifies the row address
//!
//! This function is to set row address(page address).
//!
//! \return None
//
//*****************************************************************************
void NFWriteRowAddr(unsigned long ulRowAddr)
{
	NF_ALE_SET;

	NFDataWrite(ulRowAddr);

#if(NF_DEVICE_SIZE / NF_PAGE_SIZE > 0x100)
	ulRowAddr >>= 8;
	NFDataWrite(ulRowAddr);
#endif

#if(NF_DEVICE_SIZE / NF_PAGE_SIZE > 0x10000)
	ulRowAddr >>= 8;
	NFDataWrite(ulRowAddr);
#endif

	NF_ALE_CLR;
}

//*****************************************************************************
//
//! \brief Reset NAND Flash
//!
//! \param None
//!
//! This function is to send reset command to reset NAND flash
//!
//! \return None
//
//*****************************************************************************
void NFReset(void)
{
	NF_NCE_CLR;  //chip enable
	NFCmdWrite(NF_CMD_RESET);
	while(!NF_IS_READY());
	NF_NCE_SET;  //chip disable
}

//*****************************************************************************
//
//! \brief Get ID code of NAND Flash
//!
//! \param None
//!
//! This function is to Get ID code of NAND Flash. The information is stored in
//! NandInfo structure.
//!
//! \return None
//
//*****************************************************************************
void NFIdRead(void)
{
	unsigned char i;
	unsigned char buf[4];
	NF_NCE_CLR;
	NFCmdWrite(NF_CMD_READID);
	NF_ALE_SET;
	NFDataWrite(0);
	NF_ALE_CLR;
	for(i=0;i<5;i++)
	{
		buf[i] = NFDataRead();
	}
	NF_NCE_SET;

	NandInfo.usNandFlashID = buf[0];
	NandInfo.usNandFlashID = (NandInfo.usNandFlashID << 8) | buf[1];
	NandInfo.ucNandCharacter = buf[2];
#if( NF_PAGE_SIZE > 512 )
	//
	// The characters below maybe not supported by all nandflash
	// refer to datasheet to make sure. If not, use the #else followed
	// and delete these sentences.
	//
	NandInfo.ulBlockSize = ((buf[3]&0x30)>>4) == 0 ? 0x10000 :
                               ((buf[3]&0x30)>>4) == 1 ? 0x20000 :
                               ((buf[3]&0x30)>>4) == 2 ? 0x40000 : 0x80000;

	NandInfo.ulPageSize = (buf[3]&0x3) == 0 ? 0x400 :
                              (buf[3]&0x3) == 1 ? 0x800 :
                              (buf[3]&0x3) == 2 ? 0x1000 : 0x2000;

	NandInfo.ucRDDTAreaSize = (buf[3]&0x40) == 0 ? 8 : 16;
	//NandInfo.ulCapacity = (8 << ((buf[4] & 0x0C) >> 2)) << ((buf[4] & 0x70) >> 4);
#else
	NandInfo.ulBlockSize = NF_BLOCK_SIZE;
	NandInfo.ulPageSize = NF_PAGE_SIZE;
	NandInfo.ucRDDTAreaSize = NF_SPARE_AREA_SIZE;
#endif
}

//*****************************************************************************
//
//! \brief NAND flash initialization
//!
//! \param None
//!
//! This function is to initialize NAND Flash.
//!
//! \return None
//
//*****************************************************************************
void NFInit(void)
{
	NFIOInit();
	NFReset();
	NFIdRead();
}

//*****************************************************************************
//
//! \brief Read EDC status
//!
//! \param None
//!
//! This function is to read error status register to check if operation is successful.
//! Some NAND flash might not have this character and it's only used in ¡¯Copy Back Program¡¯
//!
//! \return status value
//
//*****************************************************************************
unsigned char NFEDCStatusRead(void)
{
	unsigned char ucRes;

	NF_NCE_CLR; //chip enable
	NFCmdWrite(NF_CMD_READEDCSTATUS);
	ucRes = NFDataRead();
	NF_NCE_SET; //chip disable
	return(ucRes);
}

//*****************************************************************************
//
//! \brief Block erase
//!
//! \param ulBlockAddr specifies the block address
//!
//! This function is to erase specified block in NAND flash. Here the ulBlockAddr
//! is the block count number which can be 0 ~ max block, not is the physical address.
//!
//! \return status after the operation
//
//*****************************************************************************
unsigned char NFBlockErase(unsigned long ulBlockAddr)
{
	unsigned char i = 0, j;

	NF_NCE_CLR; //chip enable

	j = NandInfo.ulBlockSize / NandInfo.ulPageSize;
	do
	{
		j>>=1;
		i++;
	}while(j != 1);

	NFCmdWrite( NF_CMD_BLOCKERASE1 );
	NFWriteRowAddr( ulBlockAddr >> i );
	NFCmdWrite( NF_CMD_BLOCKERASE2 );

	while( !NF_IS_READY() );

	return NFStatusRead();
}

//*****************************************************************************
//
//! \brief Page Read
//!
//! \param ulPageAddr specifies the page address
//! \param pBuffer point to destination array to store read out data
//!
//! This function is to read specified page in NAND flash. Only page address
//! or row address is needed not include column address.
//!
//! \return status after the operation
//
//*****************************************************************************
unsigned char NFPageRead(unsigned long ulPageAddr, unsigned char *pBuffer)
{
	unsigned long i;

	NF_NCE_CLR; //chip enable

	NFCmdWrite(NF_CMD_READ1);
	//
	// Read from the start of the page
	//
	NFWriteColumnAddr(0);
	//
	// Set page address
	//
	NFWriteRowAddr(ulPageAddr);

#if(NF_PAGE_SIZE > 512)
	NFCmdWrite(NF_CMD_READ2);
#endif

	while(!NF_IS_READY());

	for(i = 0; i < NF_PAGE_SIZE; i++)
	{
		*pBuffer++ = NFDataRead();
	}
	return NFStatusRead();
}

//*****************************************************************************
//
//! \brief Page Write
//!
//! \param ulPageAddr specifies the page address
//! \param pBuffer point to source array to write data to NAND flash
//!
//! This function is to write specified page in NAND flash. Only page address
//! or row address is needed not include column address.
//! \note pages should be erased first before write
//!
//! \return status after the operation
//
//*****************************************************************************
unsigned char NFPageWrite(unsigned long ulPageAddr, unsigned char *pBuffer)
{
	unsigned long i;

	NF_NCE_CLR; //chip enable

	NFCmdWrite(NF_CMD_PAGEPROG1);
	//
	// Write from start of the page
	//
	NFWriteColumnAddr(0);
	//
	// Set page address
	//
	NFWriteRowAddr(ulPageAddr);

	while(!NF_IS_READY());

	for(i=0; i < NF_PAGE_SIZE; i++)
	{
		NFDataWrite(*pBuffer++);
	}
	NFCmdWrite(NF_CMD_PAGEPROG2);

	return NFStatusRead();
}

//*****************************************************************************
//
//! \brief Page Offset read
//!
//! \param usOffSet specifies the byte offset address of reading in the page
//! \param ulPageAddr specifies the page address
//! \param pBuffer point to source array to write data to store read out data
//! \param usBytesToRead specified how many bytes to read
//!
//! This function is to read specified offset address, specified page and
//! specified quantity of bytes in NAND flash.
//!
//!
//! \return status after the operation
//
//*****************************************************************************
unsigned char NFPageOffsetRead(unsigned short usOffSet,
                               unsigned long ulPageAddr,
                               unsigned char *pBuffer,
                               unsigned short usBytesToRead)
{
	unsigned short i, j;

	NF_NCE_CLR; //chip enable
	NFCmdWrite(NF_CMD_READ1);
#if(NF_PAGE_SIZE > 512)
	NFWriteColumnAddr(usOffSet);
#else
	NFWriteColumnAddr(0);
#endif
	NFWriteRowAddr(ulPageAddr);
#if(NF_PAGE_SIZE > 512)
	NFCmdWrite(NF_CMD_READ2);
#endif

	while(!NF_IS_READY());

	//
	// avoid over the boundary of page
	//
	j = (NF_PAGE_SIZE + NF_SPARE_AREA_SIZE - usOffSet) < usBytesToRead ?
			(NF_PAGE_SIZE + NF_SPARE_AREA_SIZE - usOffSet) : usBytesToRead;
#if(NF_PAGE_SIZE > 512)
	for(i = 0; i < j; i++)
	{
		*pBuffer++ = NFDataRead();
	}
#else
	//
	// dummy read to ignore the bytes before usOffSet address
	//
	for(i = 0; i < usOffSet; i++)
	{
		NFByteRead();
	}
	for(i = 0; i < j; i++)
	{
		*pBuffer++ = NFDataRead();
	}
#endif
	return NFStatusRead();
}

//*****************************************************************************
//
//! \brief Page Copy
//!
//! \param ulSrcAddr specifies the source page address
//! \param ulDestAddr specifies the destination page address
//!
//! This function is to copy specified source page to specified destination page.
//!
//! \return status after the operation
//
//*****************************************************************************
unsigned char NFPageCopy(unsigned long ulSrcPageAddr, unsigned long ulDestPageAddr)
{
	NF_NCE_CLR; //chip enable
	NFCmdWrite(NF_CMD_READYFORCOPYBACK1);
	NFWriteColumnAddr(0);
	NFWriteRowAddr(ulSrcPageAddr);
#if(NF_PAGE_SIZE > 512)
	NFCmdWrite(NF_CMD_READYFORCOPYBACK2);
#endif

	while(!NF_IS_READY());

#if(NF_PAGE_SIZE > 512)
	NFCmdWrite(NF_CMD_COPYBACKPROG1);
#else
	NFCmdWrite(0x8A);
#endif
	NFWriteColumnAddr(0);
	NFWriteRowAddr(ulDestPageAddr);
	NFCmdWrite(NF_CMD_COPYBACKPROG2);

	while(!NF_IS_READY());

	return NFStatusRead();
}

//*****************************************************************************
//
//! \brief Bytes read
//!
//! \param ulAddr specifies the byte address to read
//! \param pBuffer point to source array to write data to store read out data
//! \param usBytesToRead specified how many bytes to read
//!
//! This function is to read bytes from specified byte address in NAND flash
//! \note ulAddr do not consider the spare space. It will not read spare space and jump over.
//!
//! \return status after the operation
//
//*****************************************************************************
unsigned char NFBytesRead(unsigned long ulAddr, unsigned char *pBuffer, unsigned long ulBytesToRead)
{
	unsigned long ulBytesRead = 0;
	unsigned long ulPages = 0, ulPageAddr;
	unsigned short usOffAddr;
	unsigned short usLeftForward = 0, usLeftBehind = 0;

	ulPageAddr = ulAddr / NF_PAGE_SIZE;
	usOffAddr = ulAddr % NF_PAGE_SIZE;
	if((usOffAddr + ulBytesToRead) > NF_PAGE_SIZE)
	{
		//
		// data over one page
		//
	    usLeftForward = NF_PAGE_SIZE - usOffAddr;
	    ulPages = (ulBytesToRead - usLeftForward) / NF_PAGE_SIZE;
	    usLeftBehind = (ulBytesToRead - usLeftForward) % NF_PAGE_SIZE;
	}
	else
	{
	    usLeftForward = ulBytesToRead;
	    ulPages = 0;
	    usLeftBehind = 0;
	}

	//
	// read first part of data
	//
	NFPageOffsetRead(usOffAddr, ulPageAddr, pBuffer, usLeftForward);
	ulBytesRead += usLeftForward;
	ulPageAddr++;

	//
	// If remaining data is more than one page, read pages.
	//
	while(ulPages)
	{
		NFPageRead(ulPageAddr, &pBuffer[ulBytesRead]);
		ulBytesRead += NF_PAGE_SIZE;
		ulPageAddr++;
		ulPages--;
	}
	
	//
	// If ramaining data is less than one page, read ramaining data.
	//
	if(usLeftBehind != 0)
	{
		NFPageOffsetRead(0, ulPageAddr, &pBuffer[ulBytesRead], usLeftBehind);
	}
	return NFStatusRead();
}
