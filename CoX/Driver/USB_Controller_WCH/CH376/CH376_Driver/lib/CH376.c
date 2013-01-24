//*****************************************************************************
//
//! \file CH376.c
//! \brief hardware layer driver for CH376
//! \version V2.2.1.0
//! \date 1/5/2013
//! \author CooCox
//! \copy
//!
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
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xuart.h"
#include "stdio.h"
#include "xhw_CH376INC.h"
#include "CH376.h"

#ifdef CH376_USE_HARDWARE_SPI
#include "xhw_spi.h"
#include "xspi.h"
#endif


#ifdef CH376_INT_WIRE
#define CH376_INT_REQ() xGPIOSPinRead(CH376_INT_PIN)
#endif


#ifdef CH376_USE_HARDWARE_SPI  //hardware spi macros and read/write function define
#define CH376_SPI_CS_SET    xGPIOSPinWrite(CH376_SPI_CS_PIN,1)
#define CH376_SPI_CS_CLR    xGPIOSPinWrite(CH376_SPI_CS_PIN,0)

//*****************************************************************************
//
//! \brief end a command.
//!
//! \param None
//!
//! \details this function is to end a command only used in spi interface mode.
//!
//! \return None.
//
//*****************************************************************************
void xEndCH376Cmd(void)
{
    CH376_SPI_CS_SET;
}

//*****************************************************************************
//
//! \brief Read data from CH376.
//!
//! \param None
//!
//! \details Read data from CH376.
//!
//! \return data read out from CH376.
//
//*****************************************************************************
UINT8 xReadCH376Data( void )
{
    return(xSPISingleDataReadWrite(CH376_SPI_PORT, 0xFF));
}

//*****************************************************************************
//
//! \brief Write command to CH376.
//!
//! \param mCmd command value
//!
//! \details Write command to CH376.
//!
//! \return None.
//
//*****************************************************************************
void    xWriteCH376Cmd( UINT8 mCmd )
{
    //
    // to avoid not asserting CS PIN
    //
    CH376_SPI_CS_SET;
    CH376_SPI_CS_CLR;
    xSPISingleDataReadWrite( CH376_SPI_PORT, mCmd);
    //
    // make sure that read or write cycle must longer than 1.5us
    //
    mDelayuS(2);
}

//*****************************************************************************
//
//! \brief Write data to CH376.
//!
//! \param mData data value
//!
//! \details Write data to CH376.
//!
//! \return None.
//
//*****************************************************************************
void    xWriteCH376Data( UINT8 mData )
{
    xSPISingleDataReadWrite( CH376_SPI_PORT, mData);
}

#endif  //End of define CH376_USE_HARDWARE_SPI


#ifdef CH376_USE_SOFTWARE_SPI  //software spi macros and read/write function define
//
// if define HIGH_SPEED_IO the IO pins will be manipulated in bit band mode to save time
//
#ifdef HIGH_SPEED_IO
#define CH376_SCK_SET     xHWREGBITW(GPIO_BSRR+CH376_SCK_PORT, CH376_SCK_BIT)=1
#define CH376_SCK_CLR     xHWREGBITW(GPIO_BRR+CH376_SCK_PORT, CH376_SCK_BIT)=1
#define CH376_MOSI        xHWREGBITW(GPIO_ODR+CH376_MOSI_PORT, CH376_MOSI_BIT)
#define CH376_MISO       xHWREGBITW(GPIO_IDR+CH376_MISO_PORT, CH376_MISO_BIT)
#else
#define CH376_SCK_SET     xGPIOSPinWrite(CH376_SCK_PIN,1)
#define CH376_SCK_CLR     xGPIOSPinWrite(CH376_SCK_PIN,0)
#define CH376_MOSI(a)      xGPIOSPinWrite(CH376_MOSI_PIN,a)
#define CH376_MISO         xGPIOSPinRead(CH376_MISO_PIN)
#endif

#define CH376_SPI_CS_SET    xGPIOSPinWrite(CH376_SPI_CS_PIN,1)
#define CH376_SPI_CS_CLR    xGPIOSPinWrite(CH376_SPI_CS_PIN,0)

//*****************************************************************************
//
//! \brief end a command.
//!
//! \param None
//!
//! \details this function is to end a command only used in spi interface mode.
//!
//! \return None.
//
//*****************************************************************************
void xEndCH376Cmd(void)
{
    CH376_SPI_CS_SET;
}

//*****************************************************************************
//
//! \brief Send a byte by using software SPI.
//!
//! \param ucDat one byte to be sent.
//!
//! \details this function is to Send a byte by using software SPI.
//!
//! \return None.
//
//*****************************************************************************
void SPIDataOut(unsigned char ucDat)
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        CH376_SCK_CLR;
        if(ucDat & 0x80)
        {
#ifdef HIGH_SPEED_IO
            CH376_MOSI = 1;
#else
            CH376_MOSI(1);
#endif
        }
        else
        {
#ifdef HIGH_SPEED_IO
            CH376_MOSI = 0;
#else
            CH376_MOSI(0);
#endif
        }
        ucDat <<= 1;
        CH376_SCK_SET;
    }
}

//*****************************************************************************
//
//! \brief Receive a byte by using software SPI.
//!
//! \param None
//!
//! \details this function is to Receive a byte by using software SPI.
//!
//! \return received byte.
//
//*****************************************************************************
unsigned char SPIDataIn(void)
{
    unsigned char i;
    unsigned char dat = 0;
    for(i = 0; i < 8; i++)
    {
        CH376_SCK_CLR;
        dat <<= 1;
        if(CH376_MISO)
        {
            dat++;
        }
        CH376_SCK_SET;
    }
    return dat;
}

//*****************************************************************************
//
//! \brief Write command to CH376.
//!
//! \param mCmd command value
//!
//! \details Write command to CH376.
//!
//! \return None.
//
//*****************************************************************************
void    xWriteCH376Cmd( UINT8 mCmd )
{
    CH376_SPI_CS_SET;
    CH376_SPI_CS_CLR;
    SPIDataOut(mCmd);
    mDelayuS(2);
}

//*****************************************************************************
//
//! \brief Write data to CH376.
//!
//! \param mData data value
//!
//! \details Write data to CH376.
//!
//! \return None.
//
//*****************************************************************************
void    xWriteCH376Data( UINT8 mData )
{
    SPIDataOut(mData);
}

//*****************************************************************************
//
//! \brief Read data from CH376.
//!
//! \param None
//!
//! \details Read data from CH376.
//!
//! \return data read out from CH376.
//
//*****************************************************************************
UINT8 xReadCH376Data( void )
{
    return( SPIDataIn());
}

#endif  //End of define CH376_USE_SOFTWARE_SPI

#ifdef CH376_USE_PARALLEL  //parallel macros and read/write function define
#ifdef HIGH_SPEED_IO
#define CH376_WR_CLR    xHWREGBITW(GPIO_BRR+CH376_WR_PORT, CH376_WR_BIT)=1
#define CH376_WR_SET    xHWREGBITW(GPIO_BSRR+CH376_WR_PORT, CH376_WR_BIT)=1
#define CH376_RD_CLR    xHWREGBITW(GPIO_BRR+CH376_RD_PORT, CH376_RD_BIT)=1
#define CH376_RD_SET    xHWREGBITW(GPIO_BSRR+CH376_RD_PORT, CH376_RD_BIT)=1
#define CH376_A0_CLR    xHWREGBITW(GPIO_BRR+CH376_A0_PORT, CH376_A0_BIT)=1
#define CH376_A0_SET    xHWREGBITW(GPIO_BSRR+CH376_A0_PORT, CH376_A0_BIT)=1
#define CH376_PCS_CLR   xHWREGBITW(GPIO_BRR+CH376_PCS_PORT, CH376_PCS_BIT)=1
#define CH376_PCS_SET   xHWREGBITW(GPIO_BSRR+CH376_PCS_PORT, CH376_PCS_BIT)=1
#else
#define CH376_WR_CLR    xGPIOSPinWrite(CH376_WR_PIN,0)
#define CH376_WR_SET    xGPIOSPinWrite(CH376_WR_PIN,1)
#define CH376_RD_CLR    xGPIOSPinWrite(CH376_RD_PIN,0)
#define CH376_RD_SET    xGPIOSPinWrite(CH376_RD_PIN,1)
#define CH376_A0_CLR    xGPIOSPinWrite(CH376_A0_PIN,0)
#define CH376_A0_SET    xGPIOSPinWrite(CH376_A0_PIN,1)
#define CH376_PCS_CLR   xGPIOSPinWrite(CH376_PCS_PIN,0)
#define CH376_PCS_SET   xGPIOSPinWrite(CH376_PCS_PIN,1)
#endif
#define CH376_PARA_DATA_OUT(a) (xHWREG(GPIO_ODR+CH376_DATA_PORT)&=(0xFF00|a))

//
//! In parallel mode this function is useless, only to fit with invoking followed
//
void xEndCH376Cmd( )
{
    return;
}

//*****************************************************************************
//
//! \brief Read status from CH376.
//!
//! \param None
//!
//! \details Read status from CH376.This function is only used in parallel mode
//!
//! \return status value read out from CH376.
//
//*****************************************************************************
UINT8   xReadCH376Status( void )
{
    UINT8   res;

    CH376_A0_SET;
    CH376_PCS_CLR;
    CH376_RD_CLR;
    //
    // below sentence is intended to do a short delay.
    // CH376 require read/write pulse width >40ns
    //
    CH376_PCS_CLR;
    res = xHWREG(GPIO_IDR + CH376_DATA_PORT) & 0xFF;
    CH376_RD_SET;
    CH376_PCS_SET;
    CH376_A0_CLR;
    return res;
}

//*****************************************************************************
//
//! \brief Write command to CH376.
//!
//! \param ucCmd command value
//!
//! \details Write command to CH376.
//!
//! \return None.
//
//*****************************************************************************
void    xWriteCH376Cmd( unsigned char ucCmd )
{
    xGPIODirModeSet( CH376_DATA_PORT, 0xFF, xGPIO_DIR_MODE_OUT );
    CH376_A0_SET;
    CH376_PCS_CLR;
    CH376_WR_CLR;
    CH376_PARA_DATA_OUT( ucCmd );
    CH376_WR_SET;
    CH376_PCS_SET;
    CH376_A0_CLR;
    xGPIODirModeSet( CH376_DATA_PORT, 0xFF, xGPIO_DIR_MODE_IN );
}

//*****************************************************************************
//
//! \brief Write data to CH376.
//!
//! \param mData data value
//!
//! \details Write data to CH376.
//!
//! \return None.
//
//*****************************************************************************
void    xWriteCH376Data( unsigned char ucData )
{
    xGPIODirModeSet( CH376_DATA_PORT, 0xFF, xGPIO_DIR_MODE_OUT );
    CH376_A0_CLR;
    CH376_PCS_CLR;
    CH376_WR_CLR;
    CH376_PARA_DATA_OUT( ucData );
    CH376_WR_SET;
    CH376_PCS_SET;
    xGPIODirModeSet( CH376_DATA_PORT, 0xFF, xGPIO_DIR_MODE_IN );
}

//*****************************************************************************
//
//! \brief Read data from CH376.
//!
//! \param None
//!
//! \details Read data from CH376.
//!
//! \return data read out from CH376.
//
//*****************************************************************************
unsigned char xReadCH376Data(void)
{
    unsigned char res;
    CH376_A0_CLR;
    CH376_PCS_CLR;
    CH376_RD_CLR;
    //
    // below sentence is intended to do a short delay.
    // CH376 require read/write pulse width >40ns
    //
    CH376_PCS_CLR;
    res = xHWREG(GPIO_IDR + CH376_DATA_PORT) & 0xFF;
    CH376_RD_SET;
    CH376_PCS_SET;
    return res;
}
#endif  //End of define CH376_USE_PARALLEL

//*****************************************************************************
//
//! \brief delay specified us.
//!
//! \param n specify how many us you want to delay
//!
//! \details approximately delay for 1us depends on your system clock
//!
//! \return None
//
//*****************************************************************************
void mDelayuS(unsigned int n)
{
    while(n--)
    {
        xSysCtlDelay(30);
    }
}

//*****************************************************************************
//
//! \brief delay specified ms.
//!
//! \param n specify how many ms you want to delay
//!
//! \details approximately delay for n ms depends on your system clock
//!
//! \return None
//
//*****************************************************************************
void mDelaymS(unsigned int n)
{
    while(n--)
    {
        xSysCtlDelay(30000);
    }
}

//*****************************************************************************
//
//! \brief debugging function to show error information.
//!
//! \param ucError error code other function returned
//!
//! \details This function is intended for debugging use, error information will send to USART.
//!   Or you can modify this function to show more information.
//!
//! \return None
//
//*****************************************************************************
void    mStopIfError( UINT8 ucError )
{
    if ( ucError == USB_INT_SUCCESS ) return;
    printf( "Error: %02X\n", ucError );
    while ( 1 )
    {
        mDelaymS( 200 );
    }
}
//
//initialize USART for debugging use
//
//*****************************************************************************
//
//! \brief initialize USART for debugging use
//!
//! \param None
//!
//! \details Initialize USART1 for debugging use. Debugging will use printf function,
//!   so we use USART1 as the debugging tool. Don't forget to add and transplant printf.c.
//!
//! \return None
//
//*****************************************************************************
void    mInitSTDIO( void )
{
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOA);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
    xUARTConfigSet(USART1_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE |
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART1_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSPinTypeUART(UART1TX, PA9);
}

//*****************************************************************************
//
//! \brief MCU communication port initialize
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void	CH376PortInit( void )
{
#ifdef CH376_INT_WIRE
    xSysCtlPeripheralEnable2(CH376_INT_PORT);
    xGPIOSPinDirModeSet(CH376_INT_PIN, xGPIO_DIR_MODE_IN); //pass
    xGPIOSPinWrite(CH376_INT_PIN, 1);
#endif
#ifdef CH376_USE_HARDWARE_SPI
    xSysCtlPeripheralEnable2(CH376_SPI_CS_PORT);
    xGPIOSPinDirModeSet(CH376_SPI_CS_PIN, xGPIO_DIR_MODE_OUT);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CH376_SCK));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CH376_MOSI));
    xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(CH376_MISO));
    xSysCtlPeripheralEnable2(CH376_SPI_PORT);

    xSPinTypeSPI(SPI_CLK, CH376_SCK);
    xSPinTypeSPI(SPI_MISO, CH376_MISO);
    xSPinTypeSPI(SPI_MOSI, CH376_MOSI);
    xSPIConfigSet(CH376_SPI_PORT, CH376_CLK_FREQ, SPI_MODE_MASTER |
                  SPI_MSB_FIRST |
                  SPI_2LINE_FULL |
                  SPI_DATA_WIDTH8 |
                  SPI_FORMAT_MODE_4);
    SPISSModeConfig(CH376_SPI_PORT, SPI_CR1_SSM);
    SPISSIConfig(CH376_SPI_PORT, SPI_CR1_SSI);
    SPIEnble(CH376_SPI_PORT);
    CH376_SPI_CS_SET;
#endif  //End of CH376_USE_HARDWARE_SPI define

#ifdef CH376_USE_SOFTWARE_SPI
    xSysCtlPeripheralEnable2(CH376_SPI_CS_PORT);
    xGPIOSPinDirModeSet(CH376_SPI_CS_PIN, xGPIO_DIR_MODE_OUT);
    xSysCtlPeripheralEnable2(CH376_SCK_PORT);
    xGPIOSPinDirModeSet(CH376_SCK_PIN, xGPIO_DIR_MODE_OUT);
    xSysCtlPeripheralEnable2(CH376_MOSI_PORT);
    xGPIOSPinDirModeSet(CH376_MOSI_PIN, xGPIO_DIR_MODE_OUT);
    xSysCtlPeripheralEnable2(CH376_MISO_PORT);
    xGPIOSPinDirModeSet(CH376_MISO_PIN, xGPIO_DIR_MODE_IN);
    CH376_SPI_CS_SET;
#endif  //End of CH376_USE_SOFTWARE_SPI define

#ifdef CH376_USE_PARALLEL
    xSysCtlPeripheralEnable2(CH376_WR_PORT);
    xSysCtlPeripheralEnable2(CH376_RD_PORT);
    xSysCtlPeripheralEnable2(CH376_A0_PORT);
    xSysCtlPeripheralEnable2(CH376_PCS_PORT);
    xSysCtlPeripheralEnable2(CH376_DATA_PORT);
    xGPIOSPinDirModeSet(CH376_WR_PIN, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(CH376_RD_PIN, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(CH376_A0_PIN, xGPIO_DIR_MODE_OUT);
    xGPIOSPinDirModeSet(CH376_PCS_PIN, xGPIO_DIR_MODE_OUT);
    xGPIODirModeSet( CH376_DATA_PORT, 0xFF, xGPIO_DIR_MODE_IN );
    CH376_PCS_SET;
    CH376_WR_SET;
    CH376_RD_SET;
    CH376_A0_CLR;
#endif  //End of CH376_USE_PARALLEL define

}

//*****************************************************************************
//
//! \brief query CH376 interrupt line
//!
//! \param None
//!
//! \return TRUE or FALSE according to interrupt line.
//
//*****************************************************************************
UINT8   Query376Interrupt( void )
{
#ifdef CH376_INT_WIRE
    return( CH376_INT_REQ() ? FALSE : TRUE);
#else
#ifdef CH376_SPI_SDO_INT
    unsigned char res = 0;
    res = xGPIOSPinRead(CH376_MISO_PIN);
    return( res ? FALSE : TRUE );
#else
#ifdef CH376_USE_PARALLEL
    return( xReadCH376Status( ) & PARA_STATE_INTB ? FALSE : TRUE );
#endif
#endif
#endif
}

//*****************************************************************************
//
//! \brief Initial CH376 as USB host.
//!
//! \param None
//!
//! \return error code defined in hw_CH376INC.h.
//
//*****************************************************************************
UINT8   mInitCH376Host( void )
{
    UINT8   res;
    CH376PortInit( );
    xWriteCH376Cmd( CMD11_CHECK_EXIST );
    xWriteCH376Data( 0x65 );
    res = xReadCH376Data( );
    xEndCH376Cmd( );
    if ( res != 0x9A ) return( ERR_USB_UNKNOWN );
    xWriteCH376Cmd( CMD11_SET_USB_MODE );
    xWriteCH376Data( 0x06 );
    mDelayuS( 20 );
    res = xReadCH376Data( );
    xEndCH376Cmd( );
#ifdef  CH376_USE_SOFTWARE_SPI
#ifdef  CH376_SPI_SDO_INT
    xWriteCH376Cmd( CMD20_SET_SDO_INT );
    xWriteCH376Data( 0x16 );
    xWriteCH376Data( 0x90 );
    xEndCH376Cmd( );
#endif
#endif
    if ( res == CMD_RET_SUCCESS ) return( USB_INT_SUCCESS );
    else return( ERR_USB_UNKNOWN );
}
