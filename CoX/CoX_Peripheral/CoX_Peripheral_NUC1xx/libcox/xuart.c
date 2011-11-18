//*****************************************************************************
//
//! \file xuart.c
//! \brief Driver for the UART
//! \version V2.1.1.1
//! \date 11/14/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
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
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_uart.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xuart.h"


//*****************************************************************************
//
// This macro extracts the array index out of the peripheral clock source.
//
//*****************************************************************************
#define SYSCTL_PERIPH_INDEX_CLK(a)                                            \
                                (((a) >> 28) & 0xf)


//*****************************************************************************
//
// An array is UART callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnUARTHandlerCallbacks[3]={0};

//*****************************************************************************
//
//! \internal
//! \brief Checks a UART base address.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function determines if a UART port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
UARTBaseValid(unsigned long ulBase)
{
    return((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
           (ulBase == UART2_BASE));
}
#endif

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART0 and UART2 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART0 and UART2.
//!
//! \return None.
//
//*****************************************************************************
void 
UART02IntHandler(void)
{
    unsigned long ulUART0IntStatus,ulUART2IntStatus;

    ulUART0IntStatus = xHWREG(UART0_BASE + UART_ISR);
	
	ulUART2IntStatus = xHWREG(UART2_BASE + UART_ISR);
	
    if(g_pfnUARTHandlerCallbacks[0] != 0)
	{
        g_pfnUARTHandlerCallbacks[0](0, 0, ulUART0IntStatus, 0);
    }
	if(g_pfnUARTHandlerCallbacks[2] != 0)
    {
        g_pfnUARTHandlerCallbacks[2](0, 0, ulUART2IntStatus, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is the UART1 interrupt service.
//!
//! \param None.
//!
//! This function is a interrupt service routine of UART1
//!
//! \return None.
//
//*****************************************************************************
void 
UART1IntHandler(void)
{
    unsigned long ulUART1IntStatus;

	ulUART1IntStatus = xHWREG(UART1_BASE + UART_ISR);

    if(g_pfnUARTHandlerCallbacks[1] != 0)
    {
       g_pfnUARTHandlerCallbacks[1](0, 0, ulUART1IntStatus, 0);
    }

}

//*****************************************************************************
//
//! \internal
//! \brief The function is used to get Uart clock.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function gets the Uart clock
//! when set the bandrate of UART.
//!
//! \return Returns the Current Uart Clock.
//
//*****************************************************************************
static unsigned long UARTCLkGet(void)
{
    unsigned long clk =0 , div;
    unsigned long ulPLLSrc, ulNF, ulNR, ulNO;
    unsigned long ulMap[4] = {1, 2, 2, 4};
    //
    // Check UART Clock Source Setting.
    //
    if(((xHWREG(SYSCLK_CLKSEL1)&SYSCLK_CLKSEL1_UART_M) >> 
          SYSCLK_CLKSEL1_UART_S) == 0)         
    {
        //
        // Get External Clock From DrvSYS Setting.
        // 
        clk = 12000000;          
    }   
    else if(((xHWREG(SYSCLK_CLKSEL1)&SYSCLK_CLKSEL1_UART_M) >> 
               SYSCLK_CLKSEL1_UART_S) == 1)
    {
        //
        // According PLL Clock and UART_Divider to get clock.
        //                  
        if((xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_PLL_SRC))
        {
            ulPLLSrc = 22000000;
        }
        else
        {
            ulPLLSrc = 12*1000000;
        }
        if ((xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_PD))
        {
            clk = 0;
        }
        else
        {
            ulNF = (xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_FB_DV_M);
            ulNR = (xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_IN_DV_M) >>          \
                                           SYSCLK_PLLCON_IN_DV_S;
            ulNO = (xHWREG(SYSCLK_PLLCON) & SYSCLK_PLLCON_OUT_DV_M) >>          \
                                           SYSCLK_PLLCON_OUT_DV_S;
            clk =  ulPLLSrc*(ulNF+2)/(ulNR+2)/(ulMap[ulNO]);
        }
    }
    //
    // Clock 22Mhz.
    //    
    else
        clk = 22000000;  

    div = (xHWREG(SYSCLK_CLKDIV) & SYSCLK_CLKDIV_UART_M) >>
                                       SYSCLK_CLKDIV_UART_S;
    return clk/ (div+1);
}


//*****************************************************************************
//
//! \brief Sets the type of parity.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulParity specifies the type of parity to use.
//! 
//! Sets the type of parity to use for transmitting and expect when receiving.
//! The \e ulParity parameter must be one of \b UART_CONFIG_PAR_NONE,
//! \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE,
//! or \b UART_CONFIG_PAR_ZERO.  The last two allow direct control of the
//! parity bit; it is always either one or zero based on the mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTParityModeSet(unsigned long ulBase, unsigned long ulParity)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulParity == UART_CONFIG_PAR_NONE) ||
           (ulParity == UART_CONFIG_PAR_EVEN) ||
           (ulParity == UART_CONFIG_PAR_ODD) ||
           (ulParity == UART_CONFIG_PAR_ONE) ||
           (ulParity == UART_CONFIG_PAR_ZERO));

    //
    // Set the parity mode.
    //
    xHWREG(ulBase + UART_LCR) = ((xHWREG(ulBase + UART_LCR) &
                                    ~(UART_LCR_PBE | UART_LCR_EPE |
                                      UART_LCR_SPE)) | ulParity);
}

//*****************************************************************************
//
//! \brief Gets the type of parity currently being used.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function gets the type of parity used for transmitting data and
//! expected when receiving data.
//!
//! \return Returns the current parity settings, specified as one of
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD,
//! \b UART_CONFIG_PAR_ONE, or \b UART_CONFIG_PAR_ZERO.
//
//*****************************************************************************
unsigned long
UARTParityModeGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the current parity setting.
    //
    return(xHWREG(ulBase + UART_LCR) &
           (UART_LCR_PBE | UART_LCR_EPE | UART_LCR_SPE));
}

//*****************************************************************************
//
//! \brief Sets the Sets the RX FIFO level.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulRxLevel is the transmit FIFO interrupt level, specified as one of
//! \b UART_FIFO_1BYTES, \b UART_FIFO_4BYTES, \b UART_FIFO_8BYTES,
//! \b UART_FIFO_14BYTES, \b UART_FIFO_46BYTES, \b UART_FIFO_30BYTES.
//! or \b UART_FIFO_62BYTES.
//!
//! This function sets the FIFO level at which  receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOTriggerLevelSet(unsigned long ulBase, unsigned long ulRxLevel)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Sets the RX FIFO level.
    //
    xHWREG(ulBase + UART_FCR) &= (~(UART_FCR_RFITL_M ));
    xHWREG(ulBase + UART_FCR) |= ((ulRxLevel ));
}

//*****************************************************************************
//
//! \brief Gets the Rx FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulRxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of 
//! \b UART_FIFO_1BYTES, \b UART_FIFO_4BYTES, \b UART_FIFO_8BYTES,
//! \b UART_FIFO_14BYTES, \b UART_FIFO_46BYTES, \b UART_FIFO_30BYTES.
//! or \b UART_FIFO_62BYTES.
//!
//! This function gets the Rx FIFO level at which receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOTriggerLevelGet(unsigned long ulBase, unsigned long *pulRxLevel)
{
    unsigned long ulTemp;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Read the FIFO level register.
    //
    ulTemp = xHWREG(ulBase + UART_FCR);

    //
    // Extract the transmit and receive FIFO levels.
    //
    *pulRxLevel = ulTemp & UART_FCR_RFITL_M;
}

//*****************************************************************************
//
//! \brief Sets the configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//!
//! This function configures the UART for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter and the data
//! format in the \e ulConfig parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_6, and \b UART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE, and \b UART_CONFIG_PAR_ZERO
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigSetExpClk(unsigned long ulBase, 
                    unsigned long ulBaud, unsigned long ulConfig)
{
    unsigned long ulExtClk,ultemp,uldiv;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulBaud != 0);
    //xASSERT(ulUARTClk >= (ulBaud * UART_CLK_DIVIDER));

    //
    // Reset UART.
    //
    if (ulBase == UART0_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART0);
        SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    }
    else if (ulBase == UART1_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART1);
        SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    }
    else 
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART2);
        SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    }

    //
    // Tx FIFO Reset & Rx FIFO Reset & FIFO Mode Enable .
    //    
    xHWREG(ulBase + UART_FCR) |= UART_FCR_RX_RST | UART_FCR_TX_RST;

    //
    // Set Parity & Data bits & Stop bits .
    //  
    xHWREG(ulBase + UART_LCR) = ulConfig;

    ulExtClk = UARTCLkGet();

    //
    // Source Clock mod 16 <3 => Using Divider X =16 (MODE#1).
    //      
    if(((ulExtClk / ulBaud)%16)<3)       
    { 
        xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_EN;
        xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_ONE;
        ultemp = ulExtClk / ulBaud/16  -2;
    }
    //
    // Source Clock mod 16 >3 => Up 5% Error BaudRate.
    //     
    else                            
    {
        //
        // Try to Set Divider X = 1 (MODE#3).
        //
        xHWREG(ulBase + UART_BAUD) |= UART_BAUD_DIV_X_EN;
        xHWREG(ulBase + UART_BAUD) |= UART_BAUD_DIV_X_ONE;       
        ultemp = ulExtClk / ulBaud  -2;

        //
        // If Divider > Range .
        //
        if(ultemp > 0xFFFF)              
        {
            //
            // Try to Set Divider X up 10 (MODE#2).
            //
            xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_ONE;       
            
            for(uldiv = 8; uldiv <16;uldiv++)
            {
                if(((ulExtClk / ulBaud)%(uldiv+1))<3)
                {
                    xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_M;
                    xHWREG(ulBase + UART_BAUD) |= (uldiv << UART_BAUD_DIV_X_S);
                    ultemp = ulExtClk / ulBaud / (uldiv+1) -2;
                    break;
                }
            }
        }
    }

    xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_BRD_M;
    xHWREG(ulBase + UART_BAUD) |= (ultemp << UART_BAUD_BRD_S);
    
   
}

//*****************************************************************************
//
//! \brief Gets the current configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulBaud is a pointer to storage for the baud rate.
//! \param pulConfig is a pointer to storage for the data format.
//!
//! The baud rate and data format for the UART is determined, given an
//! explicitly provided peripheral clock (hence the ExpClk suffix).  The
//! returned baud rate is the actual baud rate; it may not be the exact baud
//! rate requested or an ``official'' baud rate.  The data format returned in
//! \e pulConfig is enumerated the same as the \e ulConfig parameter of
//! UARTConfigSetExpClk().
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigGetExpClk(unsigned long ulBase, 
                    unsigned long *pulBaud, unsigned long *pulConfig)
{
    unsigned long ulBaud,ulExtClk;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Compute the baud rate.
    //
    ulBaud = xHWREG(ulBase + UART_BAUD);
    ulExtClk = UARTCLkGet();
    
    //
    // See if mode 3 enabled.
    //
    if((ulBaud & UART_BAUD_DIV_X_EN) && (ulBaud & UART_BAUD_DIV_X_ONE))
    {
        //
        // MODE 3 .
        //
        *pulBaud = ulExtClk/((ulBaud & UART_BAUD_BRD_M) +2);
    }
    else if ((ulBaud & UART_BAUD_DIV_X_EN))
    {
        //
        // MODE 2 .
        //
        *pulBaud = ulExtClk/((ulBaud & UART_BAUD_BRD_M) +2)/
                   (((ulBaud & UART_BAUD_DIV_X_M)>>UART_BAUD_DIV_X_S) +1);
    }
    else
    {
        //
        // MODE 1 .
        //
        *pulBaud = ulExtClk/((ulBaud & UART_BAUD_BRD_M) +2)/16;
    }

    //
    // Get the parity, data length, and number of stop bits.
    //
    *pulConfig = (xHWREG(ulBase + UART_LCR) &
                  (UART_LCR_SPE | UART_LCR_WLS_M | UART_LCR_NSB |
                   UART_LCR_EPE | UART_LCR_PBE));
}

//*****************************************************************************
//
//! \brief Enables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables the SIREN control bit for IrDA mode on the UART. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnableIrDA(unsigned long ulBase )
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable SIR.
    //
    xHWREG(ulBase + UART_FUN_SEL) |= (UART_FUN_SEL_IRDA_EN);
    xHWREG(ulBase + UART_FUN_SEL) &= ~(UART_FUN_SEL_LIN_EN);

}

//*****************************************************************************
//
//! \brief Disables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the SIREN (IrDA) bits.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDisableIrDA(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable SIR .
    //
    xHWREG(ulBase + UART_FUN_SEL) &= ~(UART_FUN_SEL_IRDA_EN);
}


//*****************************************************************************
//
//! \brief Open SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulConfig is the Config of the UART port in IrDA mode.
//!
//! Open the SIREN control bit for IrDA mode on the UART. 
//!
//! The \e ulConfig parameter is the logical OR of three values: the IrDA Tx or Rx
//! Inverse, TX_SELECT.\b UART_CONFIG_IrDA_RX_EN ,and \b 
//! UART_CONFIG_IrDA_TX_EN is to enable IrDA Rx or Tx.\b UART_CONFIG_IrDA_INV_TX ,
//! \b UART_CONFIG_IrDA_INV_RX is to Inverse TX output signal or Inverse RX 
//! input signal.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIrDAConfig(unsigned long ulBase, unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable SIR.
    //
    UARTEnableIrDA(ulBase);
    
    xHWREG(ulBase + UART_IRCR) = (ulConfig);

}

//*****************************************************************************
//
//! \brief Enables LIN Function mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables the SIREN control bit for LIN Function on the UART. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnableLIN(unsigned long ulBase )
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable LIN Function.
    //
    xHWREG(ulBase + UART_FUN_SEL) |= (UART_FUN_SEL_LIN_EN);
    xHWREG(ulBase + UART_FUN_SEL) &= ~(UART_FUN_SEL_IRDA_EN);

}

//*****************************************************************************
//
//! \brief Enables 485 Function mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Enables the 485 control bit for 485 Function on the UART. 
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnable485(unsigned long ulBase )
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable LIN Function.
    //
    xHWREG(ulBase + UART_FUN_SEL) |= (UART_FUN_SEL_LIN_EN);
    xHWREG(ulBase + UART_FUN_SEL) |= (UART_FUN_SEL_IRDA_EN);

}

//*****************************************************************************
//
//! \brief Disables LIN Function mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the LIN Function bits.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDisableLIN(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable LIN Function.
    //
    xHWREG(ulBase + UART_FUN_SEL) &= ~(UART_FUN_SEL_LIN_EN);
}

//*****************************************************************************
//
//! \brief Open LIN mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulConfig is the Config of the UART port in LIN mode.
//!
//! Open the LIN mode for the UART. 
//!
//! The \e ulConfig parameter is the logical OR of three values: the LIN Tx or Rx
//! Mode, the LIN Break Field Length.\b UART_CONFIG_LIN_RX_EN ,and \b 
//! UART_CONFIG_LIN_TX_EN is to enable LIN Rx or Tx.
//!
//! \return None.
//
//*****************************************************************************
void
UARTLINConfig(unsigned long ulBase, unsigned long ulBaud, 
              unsigned long ulConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulConfig&UART_CONFIG_BKFL_MASK)<16);

    //
    // Set baud, 8 bit word length, even parity, 2 stop bits (even though the STP2
    // bit is ignored when in smartcard mode, this lets the caller read back
    // the actual setting in use).
    //
    UARTConfigSetExpClk(ulBase, ulBaud, 
                        UART_CONFIG_WLEN_8 |
                        UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_NONE);

    //
    // Enable SIR.
    //
    UARTEnableLIN(ulBase);
    
    xHWREG(ulBase + UART_LIN_BCNT) = (ulConfig);

}


//*****************************************************************************
//
//! \brief Get the know the Tx FIFO is Empty or not from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get the know the Tx FIFO is Empty or not from the specified port.
//!
//! \return Returns the xtrue if Tx FIFO is Empty or returns xfalse
//! \e xtBoolean.
//
//*****************************************************************************
xtBoolean
UARTFIFOTxIsEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));


    //
    // Return the Tx FIFO is empty or not.
    //
    return((xHWREG(ulBase + UART_FSR) & UART_FSR_TX_EF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get the know the Tx FIFO is full or not from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get the know the Tx FIFO is full or not from the specified port.
//!
//! \return Returns the xtrue if Tx FIFO is full or returns xfalse
//! \e xtBoolean.
//
//*****************************************************************************
xtBoolean
UARTFIFOTxIsFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));


    //
    // Return the Tx FIFO is full or not.
    //
    return((xHWREG(ulBase + UART_FSR) & UART_FSR_TX_FF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get the know the Tx FIFO length from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get the know the Tx FIFO length from the specified port.
//!
//! \return Returns the length of Tx FIFO
//! \e long.
//
//*****************************************************************************
long
UARTFIFOTxLength(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));


    //
    // Return the Tx FIFO length.
    //
    return((xHWREG(ulBase + UART_FSR) & UART_FSR_TXP_M) >> UART_FSR_TXP_S);
}

//*****************************************************************************
//
//! \brief Get the know the Rx FIFO is Empty or not from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get the know the Rx FIFO is Empty or not from the specified port.
//!
//! \return Returns the xtrue if Rx FIFO is Empty or returns xfalse
//! \e xtBoolean.
//
//*****************************************************************************
xtBoolean
UARTFIFORxIsEmpty(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));


    //
    // Return the Rx FIFO is empty or not.
    //
    return((xHWREG(ulBase + UART_FSR) & UART_FSR_RX_EF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get the know the Rx FIFO is full or not from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get the know the Rx FIFO is full or not from the specified port.
//!
//! \return Returns the xtrue if Rx FIFO is full or returns xfalse
//! \e xtBoolean.
//
//*****************************************************************************
xtBoolean
UARTFIFORxIsFull(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));


    //
    // Return the Rx FIFO is full or not.
    //
    return((xHWREG(ulBase + UART_FSR) & UART_FSR_RX_FF) ? xtrue : xfalse);
}

//*****************************************************************************
//
//! \brief Get the know the Rx FIFO length from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Get the know the Rx FIFO length from the specified port.
//!
//! \return Returns the length of Rx FIFO
//! \e long.
//
//*****************************************************************************
long
UARTFIFORxLength(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));


    //
    // Return the Rx FIFO length.
    //
    return((xHWREG(ulBase + UART_FSR) & UART_FSR_RXP_M) >> UART_FSR_RXP_S);
}

//*****************************************************************************
//
//! \brief Receives a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.  A \b -1 is returned if there are no characters present in the
//! receive FIFO.  The UARTCharsAvail() function should be called before
//! attempting to call this function.
//
//*****************************************************************************
long
UARTCharGetNonBlocking(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // See if there are any characters in the receive FIFO.
    //
    if(!(xHWREG(ulBase + UART_FSR) & UART_FSR_RX_EF))
    {
        //
        // Read and return the next character.
        //
        return(xHWREG(ulBase + UART_RBR));
    }
    else
    {
        //
        // There are no characters, so return a failure.
        //
        return(-1);
    }
}

//*****************************************************************************
//
//! \brief Waits for a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.  If there
//! are no characters available, this function waits until a character is
//! received before returning.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.
//
//*****************************************************************************
long
UARTCharGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until a char is available.
    //
    while(xHWREG(ulBase + UART_FSR) & UART_FSR_RX_EF)
    {
    }

    //
    // Now get the char.
    //
    return(xHWREG(ulBase + UART_RBR));
}

//*****************************************************************************
//
//! \brief Read ulLength characters from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucBuffer is the point of read buffer.
//! \param ulBase is the length of read buffer.
//!
//! Read some character from the receive FIFO for the specified port.  If there
//! are no characters available, this function waits until a character is
//! received before returning.
//!
//! \return xtrue
//
//*****************************************************************************
void
UARTBufferRead(unsigned long ulBase, unsigned char *ucBuffer,
               unsigned long ulLength)
{
    unsigned long ulCount;
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until a char is available.
    //
    for (ulCount=0; ulCount<ulLength; ulCount++)
    {
        while(xHWREG(ulBase + UART_FSR) & UART_FSR_RX_EF)
        {
        }
        ucBuffer[ulCount] = xHWREG(ulBase + UART_RBR);
    }
}


//*****************************************************************************
//
//! \brief Sends a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit FIFO for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b false is returned, and the application must retry the function later.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit FIFO or \b false if there was no space available in the transmit
//! FIFO.
//
//*****************************************************************************
xtBoolean
UARTCharPutNonBlocking(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // See if there is space in the transmit FIFO.
    //
    if(!(xHWREG(ulBase + UART_FSR) & UART_FSR_TX_FF))
    {
        //
        // Write this character to the transmit FIFO.
        //
        xHWREG(ulBase + UART_THR) = ucData;

        //
        // Success.
        //
        return(xtrue);
    }
    else
    {
        //
        // There is no space in the transmit FIFO, so return a failure.
        //
        return(xfalse);
    }
}

//*****************************************************************************
//
//! \brief Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Sends the character \e ucData to the transmit FIFO for the specified port.
//! If there is no space available in the transmit FIFO, this function waits
//! until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
void
UARTCharPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until space is available.
    //
    while(xHWREG(ulBase + UART_FSR) & UART_FSR_TX_FF)
    {
    }

    //
    // Send the char.
    //
    xHWREG(ulBase + UART_THR) = ucData;
}


//*****************************************************************************
//
//! \brief Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Sends the character \e ucData to the transmit FIFO for the specified port.
//! If there is no space available in the transmit FIFO, this function waits
//! until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
void
UARTBufferWrite(unsigned long ulBase, unsigned char *ucBuffer,
                unsigned long ulLength)
{
    
    unsigned long ulCount;
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Wait until a char is available.
    //
    for (ulCount=0; ulCount<ulLength; ulCount++)
    {
        while((xHWREG(ulBase + UART_FSR) & UART_FSR_TX_FF))
        {
        }
        xHWREG(ulBase + UART_THR) = ucBuffer[ulCount];
    }
}

//*****************************************************************************
//
//! \brief Causes a BREAK to be sent.
//!
//! \param ulBase is the base address of the UART port.
//! \param bBreakState controls the output level.
//!
//! Calling this function with \e bBreakState set to \b true asserts a break
//! condition on the UART.  Calling this function with \e bBreakState set to
//! \b false removes the break condition.  For proper transmission of a break
//! command, the break must be asserted for at least two complete frames.
//!
//! \return None.
//
//*****************************************************************************
void
UARTBreakCtl(unsigned long ulBase, xtBoolean bBreakState)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Set the break condition as requested.
    //
    xHWREG(ulBase + UART_LCR) =
        (bBreakState ?
         (xHWREG(ulBase + UART_LCR) | UART_LCR_BCB) :
         (xHWREG(ulBase + UART_LCR) & ~(UART_LCR_BCB)));
}

//*****************************************************************************
//
//! \brief Enables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b UART_INT_LIN    - LIN RX Break Field Detected Interrupt
//! - \b UART_INT_WAKEUP - Wake up CPU function
//! - \b UART_INT_BUFERR - Buffer Error Interrupt
//! - \b UART_INT_RTO    - Rx Time out Interrupt
//! - \b UART_INT_MOS    - RModem Status Interrupt
//! - \b UART_INT_RLS    - Receive Line Status Interrupt
//! - \b UART_INT_THRE   - Transmit Holding Register Empty
//! - \b UART_INT_RDA    - Receive Data Available Interrupt
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Enable the specified interrupts.
    //
    xHWREG(ulBase + UART_IER) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the specified UART Port.
//!
//! \param ulPort is the base address of the UART port.
//! \param xtI2CCallback is callback for the specified UART Port.
//!
//! Init interrupts callback for the specified UART Port.
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntCallbackInit(unsigned long ulBase, 
                    xtEventCallback xtUARTCallback)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    if (ulBase == UART0_BASE)
    {
        g_pfnUARTHandlerCallbacks[0] = xtUARTCallback;
    }
    else if (ulBase == UART1_BASE)
    {
        g_pfnUARTHandlerCallbacks[1] = xtUARTCallback;    
    }
    else
    {
        g_pfnUARTHandlerCallbacks[2] = xtUARTCallback;
    }
}

//*****************************************************************************
//
//! \brief Enables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the one of any of the following:
//!
//! - \b UART_INT_LIN    - LIN RX Break Field Detected Interrupt
//! - \b UART_INT_WAKEUP - Wake up CPU function
//! - \b UART_INT_BUFERR - Buffer Error Interrupt
//! - \b UART_INT_RTO    - Rx Time out Interrupt
//! - \b UART_INT_MOS    - RModem Status Interrupt
//! - \b UART_INT_RLS    - Receive Line Status Interrupt
//! - \b UART_INT_THRE   - Transmit Holding Register Empty
//! - \b UART_INT_RDA    - Receive Data Available Interrupt
//!
//! \return None.
//
//*****************************************************************************
xtBoolean
UARTIntEnableGet(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Get enable the specified interrupts.
    //
    return (xHWREG(ulBase + UART_IER) & (ulIntFlags & 0xFF)) ? xtrue : xfalse;
}


//*****************************************************************************
//
//! \brief Disables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to UARTIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Disable the specified interrupts.
    //
    xHWREG(ulBase + UART_IER) &= ~(ulIntFlags);
}


//*****************************************************************************
//
//! \brief Gets the current interrupt status.
//!
//! \param ulBase is the base address of the UART port.
//! \param bMasked is \b false if the raw interrupt status is required and
//! \b true if the masked interrupt status is required.
//!
//! This returns the interrupt status for the specified UART.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in UARTIntEnable().
//
//*****************************************************************************
unsigned long
UARTIntStatus(unsigned long ulBase, xtBoolean bMasked)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(xHWREG(ulBase + UART_ISR));
    }
    else
    {
        return(xHWREG(ulBase + UART_ISR));
    }
}

//*****************************************************************************
//
//! \brief Clears UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified UART interrupt sources are cleared, so that they no longer
//! assert.  This function must be called in the interrupt handler to keep the
//! interrupt from being recognized again immediately upon exit.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to UARTIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Clear the requested interrupt sources.
    //
    if ((ulIntFlags & UART_INT_RDA) == UART_INT_RDA)
    {
        xHWREG(ulBase + UART_RBR);
    }
    if ((ulIntFlags & UART_INT_THRE) == UART_INT_THRE)
    {
        xHWREG(ulBase + UART_RBR) = 0;
    }
    if ((ulIntFlags & UART_INT_RLS) == UART_INT_RLS)
    {
        xHWREG(ulBase + UART_FSR) |= UART_FSR_BIF | UART_FSR_FEF | 
                                     UART_FSR_PEF;
    }
    if ((ulIntFlags & UART_INT_MOS) == UART_INT_MOS)
    {
        xHWREG(ulBase + UART_MSR) |= UART_MSR_DCTSF;
    }
    if ((ulIntFlags & UART_INT_RTO) == UART_INT_RTO)
    {
        xHWREG(ulBase + UART_RBR);
    }
    if ((ulIntFlags & UART_INT_LIN) == UART_INT_LIN)
    {
        xHWREG(ulBase + UART_ISR) |= UART_ISR_LINRXB_IF;
    }
    if ((ulIntFlags & UART_INT_BUFERR) == UART_INT_BUFERR)
    {
        xHWREG(ulBase + UART_FSR) |= UART_FSR_TXO_IF | UART_FSR_RXOIF;
    }
}

//*****************************************************************************
//
//! \brief Enable UART DMA operation.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulDMAFlags is a bit mask of the DMA features to enable.
//!
//! The specified UART DMA features are enabled.  The UART can be
//! configured to use DMA for transmit or receive, and to disable
//! receive if an error occurs.  The \e ulDMAFlags parameter is the
//! logical OR of any of the following values:
//!
//! - UART_DMA_RX - enable DMA for receive
//! - UART_DMA_TX - enable DMA for transmit
//!
//! \note The uDMA controller must also be set up before DMA can be used
//! with the UART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDMAEnable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Set the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + UART_IER) |= ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Disable UART DMA operation.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulDMAFlags is a bit mask of the DMA features to disable.
//!
//! This function is used to disable UART DMA features that were enabled
//! by UARTDMAEnable().  The specified UART DMA features are disabled.  The
//! \e ulDMAFlags parameter is the logical OR of any of the following values:
//!
//! - UART_DMA_RX - disable DMA for receive
//! - UART_DMA_TX - disable DMA for transmit
//!
//! \return None.
//
//*****************************************************************************
void
UARTDMADisable(unsigned long ulBase, unsigned long ulDMAFlags)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Clear the requested bits in the UART DMA control register.
    //
    xHWREG(ulBase + UART_IER) &= ~ulDMAFlags;
}

//*****************************************************************************
//
//! \brief Sets the states of the RTS modem control signals and trigger level.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulControl is a bit-mapped flag indicating how the modem control bits
//! should be set.
//!
//! Sets the states of the RTS modem handshake outputs from the UART.
//!
//! The \e ulControl parameter is the logical OR of any of the following:
//!
//! - \b UART_TRIGGER_RTS_H - The Modem Control DTR signal on high level triggered
//! - \b UART_TRIGGER_RTS_L - The Modem Control RTS signal on low level triggered
//! - \b UART_OUTPUT_RTS_SET - The Modem Control RTS signal 
//!
//! \note It is not available on UART2.
//!
//! \return None.
//
//*****************************************************************************
void
UARTModemControlSet(unsigned long ulBase, unsigned long ulControl)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE) );

    //
    // Set the appropriate modem control output bits.
    //
    xHWREG(ulBase + UART_MCR) &= ~(UART_MCR_RTS | UART_MCR_LEV_RTS);
    xHWREG(ulBase + UART_MCR) |= (ulControl);
}

//*****************************************************************************
//
//! \brief Clears the states of the RTS modem control signals.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulControl is a bit-mapped flag indicating how modem control bits
//! should be Clear.
//!
//! Clears the states of the RTS modem handshake outputs from the UART.
//!
//! The \e ulControl parameter is the logical OR of any of the following:
//!
//! - \b UART_OUTPUT_RTS_SET - The Modem Control RTS signal 
//!
//! \note It is not available on UART2.
//!
//! \return None.
//
//*****************************************************************************
void
UARTModemControlClear(unsigned long ulBase, unsigned long ulControl)
{

    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE) );

    //
    // Set the appropriate modem control output bits.
    //
    xHWREG(ulBase + UART_MCR) &= ~(ulControl & UART_MCR_RTS);
}

//*****************************************************************************
//
//! \brief Gets the states of the RTS modem control signals.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current states of each of the UART modem control signals,
//! RTS.
//!
//! \note It is not available on UART2.
//!
//! \return Returns the states of the handshake output signals. 
//! \b UART_OUTPUT_RTS_GET_H and\b UART_OUTPUT_RTS_GET_L
//
//*****************************************************************************
unsigned long
UARTModemControlGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE) );
    
    return(xHWREG(ulBase + UART_MCR) & (UART_MCR_RTS_ST));

}

//*****************************************************************************
//
//! \brief Sets the states of the CTS modem control signals trigger level.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulControl is a bit-mapped flag indicating how the modem control bits
//! should be set.
//!
//! Sets the states of the RTS modem handshake outputs trigger level from the UART.
//!
//! The \e ulCtsTirg parameter is the logical OR of any of the following:
//!
//! - \b UART_TRIGGER_CTS_H - The Modem Control DTR signal on high level triggered
//! - \b UART_TRIGGER_CTS_L - The Modem Control RTS signal on low level triggered
//!
//! \note It is not available on UART2.
//!
//! \return None.
//
//*****************************************************************************
void
UARTModemStatusSet(unsigned long ulBase, unsigned long ulCtsTirg)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE) );

    //
    // Set the appropriate modem control output bits.
    //
    xHWREG(ulBase + UART_MSR) &= ~(UART_TRIGGER_CTS_H);
    xHWREG(ulBase + UART_MSR) |= (ulCtsTirg);
}


//*****************************************************************************
//
//! \brief Gets the states of the CTS modem status signals.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current states of each of the UART modem status signals,
//! CTS.
//!
//! \note It is not available on UART2.
//!
//! \return Returns the states of the handshake output signals.  
//! \b UART_INPUT_CTS_H and\b UART_INPUT_CTS_L
//
//*****************************************************************************
unsigned long
UARTModemStatusGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE) );

    return(xHWREG(ulBase + UART_MSR) & (UART_MSR_CTS_ST));
}


//*****************************************************************************
//
//! \brief Sets the UART hardware flow control mode to be used.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulMode indicates the flow control modes to be used.  This is a
//! logical OR combination of values \b UART_FLOWCONTROL_TX and \b
//! UART_FLOWCONTROL_RX to enable hardware transmit (CTS) and receive (RTS)
//! flow control or \b UART_FLOWCONTROL_NONE to disable hardware flow control.
//!
//! Sets the required hardware flow control modes.  If \e ulMode contains
//! flag \b UART_FLOWCONTROL_TX, data is only transmitted if the incoming CTS
//! signal is asserted. If \e ulMode contains flag \b UART_FLOWCONTROL_RX,
//! the RTS output is controlled by the hardware and is asserted only when
//! there is space available in the receive FIFO.  If no hardware flow control
//! is required, UART_FLOWCONTROL_NONE should be passed.
//!
//! \note It is not available on UART2.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFlowControlSet(unsigned long ulBase, unsigned long ulMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE));
    xASSERT((ulMode & ~(UART_FLOWCONTROL_TX | UART_FLOWCONTROL_RX)) == 0);

    //
    // Set the flow control mode as requested.
    //
    xHWREG(ulBase + UART_IER) = ((xHWREG(ulBase + UART_IER) &
                                 ~(UART_FLOWCONTROL_TX |
                                   UART_FLOWCONTROL_RX)) | ulMode);
}

//*****************************************************************************
//
//! \brief Returns the UART hardware flow control mode currently in use.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Returns the current hardware flow control mode.
//!
//! \note It is not available on UART2.
//!
//! \return Returns the current flow control mode in use.  This is a
//! logical OR combination of values \b UART_FLOWCONTROL_TX if transmit
//! (CTS) flow control is enabled and \b UART_FLOWCONTROL_RX if receive (RTS)
//! flow control is in use.  If hardware flow control is disabled, \b
//! UART_FLOWCONTROL_NONE will be returned.
//
//*****************************************************************************
unsigned long
UARTFlowControlGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE));

    return(xHWREG(ulBase + UART_IER) & (UART_FLOWCONTROL_TX |
                                         UART_FLOWCONTROL_RX));
}

//*****************************************************************************
//
//! \brief Gets current receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns the current state of each of the 3 receiver error
//! sources.  
//!
//! \return Returns a logical OR combination of the receiver error flags,
//! \b UART_RXERROR_FRAMING, \b UART_RXERROR_PARITY, \b UART_RXERROR_BREAK
//! and \b UART_RXERROR_OVERRUN.
//
//*****************************************************************************
unsigned long
UARTRxErrorGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Return the current value of the receive status register.
    //
    return(xHWREG(ulBase + UART_FSR) & 0x000000FF);
}

//*****************************************************************************
//
//! \brief Clears all reported receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function is used to clear all receiver error conditions reported via
//! UARTRxErrorGet().  If using the overrun, framing error, parity error or
//! break interrupts, this function must be called after clearing the interrupt
//! to ensure that later errors of the same type trigger another interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
UARTRxErrorClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));

    //
    // Any write to the Error Clear Register will clear all bits which are
    // currently set.
    //
    xHWREG(ulBase + UART_FCR) &= ~0xFF;
}


//*****************************************************************************
//
//! \brief Sets the Rx Time Out Value.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulValue Time out value
//!
//! Sets the Rx Time Out Value
//!
//! \return None.
//
//*****************************************************************************
void
UARTRxTimeOutSet(unsigned long ulBase, unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == UART0_BASE) ||(ulBase == UART1_BASE));
    xASSERT(ulValue < 64);

    //
    // Set the flow control mode as requested.
    //
    xHWREG(ulBase + UART_TOR) = ulValue;

    xHWREG(ulBase + UART_IER) |= UART_IER_TIME_OUT_EN;
}

//*****************************************************************************
//
//! \brief Enables SIR (IrDA) mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//! \param ulMode is the IrDA mode. 
//!
//! This function configures the UART IrDA for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter,  the data
//! format in the \e ulConfig parameter, and the ulMode is provided in the
//! \e ulMode parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b xUART_CONFIG_WLEN_8,
//! \b xUART_CONFIG_WLEN_7, \b xUART_CONFIG_WLEN_6, and \b xUART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \bX UART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE,  and
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit, 
//! even parity bit, odd parity bit, parity bit always one, and 
//! parity bit always zero, respectively).
//!
//! The \e ulMode parameter can be values:
//! - \b xUART_IRDA_MODE_NORMAL - IrDA normal mode
//!
//! \note SIR (IrDA) operation is not supported on Sandstorm-class devices.
//!
//! \return None.
//
//*****************************************************************************
void 
xUARTIrDAConfig(unsigned long ulBase, unsigned long ulBaud, 
                unsigned long ulConfig, unsigned long ulMode)
{
    unsigned long ulExtClk,ultemp,uldiv;

    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(ulBaud != 0);
    //xASSERT(ulUARTClk >= (ulBaud * UART_CLK_DIVIDER));

    //
    // Reset UART.
    //
    if (ulBase == UART0_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART0);
        SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    }
    else if (ulBase == UART1_BASE)
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART1);
        SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    }
    else 
    {
        SysCtlPeripheralReset(SYSCTL_PERIPH_UART2);
        SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);
    }

    //
    // Tx FIFO Reset & Rx FIFO Reset & FIFO Mode Enable .
    //    
    xHWREG(ulBase + UART_FCR) |= UART_FCR_RX_RST | UART_FCR_TX_RST;

    //
    // Set Parity & Data bits & Stop bits .
    //  
    xHWREG(ulBase + UART_LCR) = ulConfig;

    ulExtClk = UARTCLkGet();

    //
    // Source Clock mod 16 <3 => Using Divider X =16 (MODE#1).
    //      
    if(((ulExtClk / ulBaud)%16)<3)       
    { 
        xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_EN;
        xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_ONE;
        ultemp = ulExtClk / ulBaud/16  -2;
    }
    //
    // Source Clock mod 16 >3 => Up 5% Error BaudRate.
    //     
    else                            
    {
        //
        // Try to Set Divider X = 1 (MODE#3).
        //
        xHWREG(ulBase + UART_BAUD) |= UART_BAUD_DIV_X_EN;
        xHWREG(ulBase + UART_BAUD) |= UART_BAUD_DIV_X_ONE;       
        ultemp = ulExtClk / ulBaud  -2;

        //
        // If Divider > Range .
        //
        if(ultemp > 0xFFFF)              
        {
            //
            // Try to Set Divider X up 10 (MODE#2).
            //
            xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_ONE;       
            
            for(uldiv = 8; uldiv <16;uldiv++)
            {
                if(((ulExtClk / ulBaud)%(uldiv+1))<3)
                {
                    xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_DIV_X_M;
                    xHWREG(ulBase + UART_BAUD) |= (uldiv << UART_BAUD_DIV_X_S);
                    ultemp = ulExtClk / ulBaud / (uldiv+1) -2;
                    break;
                }
            }
        }
    }

    xHWREG(ulBase + UART_BAUD) &= ~UART_BAUD_BRD_M;
    xHWREG(ulBase + UART_BAUD) |= (ultemp << UART_BAUD_BRD_S);
}

//*****************************************************************************
//
//! \brief Enables transmitting or receiving.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulBlock is the block to enable. it is the logical OR of 
//! these values: \b UART_BLOCK_UART, \b UART_BLOCK_TX, \b UART_BLOCK_RX.
//!
//! Sets the UARTEN, or TXE or RXE bits.
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnable(unsigned long ulBase, unsigned long ulBlock)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));
    xASSERT((ulBlock & ~(0 | 0x80 | 0x40)) == 0);

    //
    // Enable RX | TX | the UART.
    //
    xHWREG(ulBase + UART_LIN_BCNT) |= ulBlock & (UART_LIN_BCNT_RX_EN | 
                                      UART_LIN_BCNT_TX_EN);
    if (ulBlock & UART_LIN_BCNT_TX_EN)
    {
        xHWREG(ulBase + UART_IRCR) |= UART_IRCR_TX_SELECT;
    }
    else
    {
        xHWREG(ulBase + UART_IRCR) &= ~UART_IRCR_TX_SELECT;
    }
}


//*****************************************************************************
//
//! \brief Open 485 mode on the specified UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ul485Config is the Config of the UART port in 485 mode.
//! \param ulUARTConfig is the Config for UART.
//!
//! Open the 485 mode for the UART. 
//!
//! The baud rate is provided in the \e ulBaud parameter and the data
//! format in the \e ulUARTConfig parameter.
//!
//! The \e ulUARTConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_6, and \b UART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE, and \b UART_CONFIG_PAR_ZERO
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//! The \e ul485Config parameter is the logical OR of five values: the 
//! Address match value,RS-485 Address Detection Enable,RS-485 Auto Direction
//! Mode (AUD),RS-485 Auto Address Detection Operation Mode (AAD),RS-485 Normal
//! Multi-drop Operation Mode (NMM).
//!
//! \return None.
//
//*****************************************************************************
void
UART485Config(unsigned long ulBase, unsigned long ulBaud,
              unsigned long ul485Config, unsigned long ulUARTConfig)
{
    //
    // Check the arguments.
    //
    xASSERT(UARTBaseValid(ulBase));


    //
    // Set baud, 8 bit word length, even parity, 2 stop bits (even though the STP2
    // bit is ignored when in smartcard mode, this lets the caller read back
    // the actual setting in use).
    //
    UARTConfigSetExpClk(ulBase, ulBaud, ulUARTConfig);

    //
    // Enable 485.
    //
    UARTEnable485(ulBase);
    xHWREG(ulBase + UART_LIN_BCNT) &= 0xFFFFFF00;
    xHWREG(ulBase + UART_LIN_BCNT) |= ul485Config;

}

