#include "xhw_types.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xdebug.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"

//*****************************************************************************
//
// An array for uart callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnWDTHandlerCallbacks[4] = {0};

//*****************************************************************************
//
//! \brief  UART 0 interrupt handler.
//!         This function is the UART interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void UART0IntHandler(void)
{
    if(g_pfnWDTHandlerCallbacks != 0)
    {
        g_pfnWDTHandlerCallbacks[0](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  UART 1 interrupt handler.
//!         This function is the UART interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void UART1IntHandler(void)
{
    if(g_pfnWDTHandlerCallbacks != 0)
    {
        g_pfnWDTHandlerCallbacks[1](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  UART 2 interrupt handler.
//!         This function is the UART interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void UART2IntHandler(void)
{
    if(g_pfnWDTHandlerCallbacks != 0)
    {
        g_pfnWDTHandlerCallbacks[2](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  UART 3 interrupt handler.
//!         This function is the UART interrupt handler, it simple execute the
//!         callback function if there be one.
//!
//! \param  None.
//!
//! \return None.
//!
//
//*****************************************************************************
void UART3IntHandler(void)
{
    if(g_pfnWDTHandlerCallbacks != 0)
    {
        g_pfnWDTHandlerCallbacks[3](0, 0, 0, 0);
    }
    else
    {
        while(1);
    }
}

//*****************************************************************************
//
//! \brief  Register user interrupts callback function  for the UART.
//!
//! \param  [in] ulBase is the base address of the UART port.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] xtPortCallback is user callback for the UART.
//!
//! \return None.
//
//*****************************************************************************
unsigned long UARTIntCallbackInit(unsigned long ulBase,
        xtEventCallback pfnCallback)
{
    // Check the parameters.
    xASSERT( (ulBase == UART0_BASE) ||
             (ulBase == UART1_BASE) ||
             (ulBase == UART2_BASE) ||
             (ulBase == UART3_BASE) );
    xASSERT(pfnCallback != 0);

    // Register user call back function.
    switch(ulBase)
    {
        case UART0_BASE:
            {
                g_pfnWDTHandlerCallbacks[0] = pfnCallback;
                break;
            }

        case UART1_BASE:
            {
                g_pfnWDTHandlerCallbacks[1] = pfnCallback;
                break;
            }

        case UART2_BASE:
            {
                g_pfnWDTHandlerCallbacks[2] = pfnCallback;
                break;
            }

        case UART3_BASE:
            {
                g_pfnWDTHandlerCallbacks[3] = pfnCallback;
                break;
            }
    }

    return (0);

}

//*****************************************************************************
//
//! \internal
//! \brief  Configure UART baud rate.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulBaudrate is target baud rate. which can be most common value
//!              e.g. 9600/115200.
//!
//! \return Show whether configure baud rate or not.
//!         - xtrue  configure success.
//!         - xflase configure failure.
//!
//! \note   This function is only for internal use!
//
//*****************************************************************************
static xtBoolean UartSetDivisors(unsigned long ulBase, unsigned long ulBaudrate)
{
    unsigned long      ulPeriClk     = 0;
    unsigned long      d             = 0;
    unsigned long      m             = 0;
    unsigned long      bestd         = 0;
    unsigned long      bestm         = 0;
    unsigned long      tmp           = 0;
    unsigned long      current_error = 0;
    unsigned long      best_error    = 0;
    unsigned long      max_error     = 3;
    unsigned long      recalcbaud    = 0;
    unsigned long long best_divisor  = 0;
    unsigned long long divisor       = 0;

    switch(ulBase)
    {
        case UART0_BASE:
            {
                ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART0);
                break;
            }

        case UART1_BASE:
            {
                ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART1);
                break;
            }

        case UART2_BASE:
            {
                ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART2);
                break;
            }

        case UART3_BASE:
            {
                ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART3);
                break;
            }
        default:                         // Error
            {
                while(1);
            }
    }


    // In the Uart IP block, baud rate is calculated using FDR and DLL-DLM registers
    // The formula is :
    // BaudRate= uPeriClk * (mulFracDiv/(mulFracDiv+dividerAddFracDiv) / (16 * (DLL)
    // It involves floating point calculations. That's the reason the formulae are adjusted with
    // Multiply and divide method.
    // The value of mulFracDiv and dividerAddFracDiv should comply to the following expressions:
    // 0 < mulFracDiv <= 15, 0 <= dividerAddFracDiv <= 15

    // Worst case
    best_error = 0xFFFFFFFF;
    bestd = 0;
    bestm = 0;
    best_divisor = 0;

    for (m = 1 ; m <= 15 ;m++)
    {
        for (d = 0 ; d < m ; d++)
        {
            divisor       = ((unsigned long long)ulPeriClk<<28)*m/(ulBaudrate*(m+d));
            current_error = divisor & 0xFFFFFFFF;

            tmp = divisor>>32;

            // Adjust error
            if(current_error > ((unsigned long)1<<31))
            {
                current_error = -current_error;
                tmp++;
            }

            if(tmp<1 || tmp>65536)
            {
                continue;
            }

            if( current_error < best_error)
            {
                best_error   = current_error;
                best_divisor = tmp;
                bestd        = d;
                bestm        = m;
                if(best_error == 0)
                {
                    break;
                }
            }
        }

        if (best_error == 0)
        {
            break;
        }
    }

    // Can not find best match
    if(best_divisor == 0)
    {
        return xfalse;
    }

    recalcbaud = (ulPeriClk>>4) * bestm/(best_divisor * (bestm + bestd));

    // Reuse best_error to evaluate baud error
    if(ulBaudrate > recalcbaud)
    {
        best_error = ulBaudrate - recalcbaud;
    }
    else
    {
        best_error = recalcbaud -ulBaudrate;
    }

    best_error = best_error * 100 / ulBaudrate;

    if (best_error < max_error)
    {
        if(ulBase == UART1_BASE)
        {
            // Nothing to do Now.
        }
        else
        {
            //Configure DLM/DLL
            xHWREG(ulBase + LCR) |= LCR_DLAB;
            xHWREG(ulBase + DLM) = (best_divisor >> 8) & 0xFF;
            xHWREG(ulBase + DLL) = (best_divisor >> 0) & 0xFF;

            // DLAB Must be zero.
            xHWREG(ulBase + LCR) &= ~LCR_DLAB;
            bestd &= (unsigned long)0x0F;
            bestm = (bestm << 4) & (unsigned long)0xF0;
            xHWREG(ulBase + FDR) = bestd | bestm;
        }

        return (xtrue);                                    // Success configure Baud registers.
    }

    return (xfalse);                                       // Failure to configure Baud registers.
}

//*****************************************************************************
//
//! \brief  Receive an byte via uart.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \return The byte received.
//!
//! \note   This function will exit unless receive an byte successfully.
//
//*****************************************************************************
unsigned char UARTByteRead(unsigned long ulBase)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    // DLAB MUST be zero.
    xHWREG(ulBase + LCR) &= ~LCR_DLAB;

    // Waiting UART receive one byte.
    do
    {
        ulTmpReg = xHWREG(ulBase + LSR);
        ulTmpReg &= LSR_RDR;
    }while(0 == ulTmpReg);

    // Read the byte.
    ulTmpReg = xHWREG(ulBase + RBR);

    return (ulTmpReg);
}

//*****************************************************************************
//
//! \brief  Transmit an byte via uart.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ucData is the byte you want to transmit.
//!
//! \return None.
//!
//! \note   This function will exit unless transmit an byte successfully.
//
//*****************************************************************************
void UARTByteWrite(unsigned long ulBase, unsigned char ucData)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    // DLAB MUST be zero.
    xHWREG(ulBase + LCR) &= ~LCR_DLAB;

    // Waiting UART receive one byte.
    do
    {
        ulTmpReg = xHWREG(ulBase + LSR);
        ulTmpReg &= LSR_THRE;
    }while(0 == ulTmpReg);

    // Write Byte into FIFO.
    xHWREG(ulBase + THR) = (unsigned long) ucData;    // UART Data register.
}

//*****************************************************************************
//
//! \brief  Receive an byte via uart not blocking.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [out] ucpData is the pointer point to the address of receive buffer.
//!               This parameter NUST NOT be NULL.
//!
//! \return Returns the character read from the specified port, cast as a
//!         \e long. A \b -1 is returned if there are no characters present in the
//!         receive FIFO.
//!
//! \note   Unlike \ref UARTByteRead, when no data available, it will exit
//!         inmmediately.
//
//*****************************************************************************
unsigned long UARTByteReadNoBlocking(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    // DLAB MUST be zero.
    xHWREG(ulBase + LCR) &= ~LCR_DLAB;

    // Receive one byte ?
    if( xHWREG(ulBase + LSR) &  LSR_RDR)  // Yes
    {
        // Read the byte.
        return xHWREG(ulBase + RBR);
    }
    else                                  // No
    {
        return (-1);
    }

}

//*****************************************************************************
//
//! \brief  Transmit an byte via uart not blocking.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ucData is the byte you want to transmit.
//!
//! \return Indicate the whether transmit byte sucessfully.
//!         - xtrue   Have received an byte succssfully.
//!         - xflase  Have not received an byte.
//!
//! \note   Unlike \ref UARTByteWrite, when FIFO is full, it will exit inmmediately.
//
//*****************************************************************************
xtBoolean UARTByteWriteNoBlocking(unsigned long ulBase, unsigned char ucData)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    // DLAB MUST be zero.
    xHWREG(ulBase + LCR) &= ~LCR_DLAB;

    // Transmitter FIFO is empty ?
    ulTmpReg = xHWREG(ulBase + LSR);
    if(ulTmpReg & LSR_THRE)            // Yes
    {
        // Write Byte into FIFO.
        xHWREG(ulBase + THR) = (unsigned long)ucData;
        return (xtrue);
    }
    else                               // No
    {
        return (xfalse);
    }

}

//*****************************************************************************
//
//! \brief  Send string.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [out] pStr is the target string.
//!
//! \return None.
//!
//! \note   This function will continue transmit until meet '\0' in string.
//
//*****************************************************************************
void UARTStrSend(unsigned long ulBase, unsigned char * pStr)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    while(NULL != *pStr)
    {
        UARTByteWrite(ulBase, *pStr++);
    }
}

//*****************************************************************************
//
//! \brief  Transmit a block of data via uart.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] pBuf is the buffer address.
//!
//! \param  [in] ulLen is the size of buffer, ulLen Bytes.
//!
//! \return None.
//
//*****************************************************************************
void UARTBufWrite(unsigned long ulBase, unsigned char * pBuf, unsigned long ulLen)
{
    unsigned long i = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    for(i = 0; i < ulLen; i++)
    {
        UARTByteWrite(ulBase, pBuf[i]);
    }
}

//*****************************************************************************
//
//! \brief  Receive a block of data via uart.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [out] pBuf is the buffer address.
//!
//! \param  [in] ulLen is the size of buffer, ulLen Bytes.
//!
//! \return None.
//
//*****************************************************************************
void UARTBufRead(unsigned long ulBase, unsigned char * pBuf, unsigned long ulLen)
{
    unsigned long i = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    for(i = 0; i < ulLen; i++)
    {
        pBuf[i] = UARTByteRead(ulBase);
    }
}

//*****************************************************************************
//
//! \brief  Enable UART Interrupt.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulIntFlags is the interrupt flag to be enabled. which can be
//!              one of the following value:
//!              - \ref INT_RDA
//!              - \ref INT_THRE
//!              - \ref INT_RLS
//!              - \ref INT_MODEM
//!              - \ref INT_CTS
//!              - \ref INT_ABEO
//!              - \ref INT_ABTO
//!
//! \return None.
//
//*****************************************************************************
void UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    xASSERT( (ulIntFlags & ~(
                            INT_RDA   |
                            INT_THRE  |
                            INT_RLS   |
                            INT_MODEM |
                            INT_CTS   |
                            INT_ABEO  |
                            INT_ABTO
                    )
             ) == 0);


    // DLAB MUST be zero.
    xHWREG(ulBase + LCR) &= ~LCR_DLAB;

    // Set interrupt control bit.
    xHWREG(ulBase + IER) |= ulIntFlags;
}

//*****************************************************************************
//
//! \brief  Disable UART Interrupt.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulIntFlags is the interrupt flag to be disabled. which can be
//!              one of the following value:
//!              - \ref INT_RDA
//!              - \ref INT_THRE
//!              - \ref INT_RLS
//!              - \ref INT_MODEM
//!              - \ref INT_CTS
//!              - \ref INT_ABEO
//!              - \ref INT_ABTO
//!
//! \return None.
//
//*****************************************************************************
void UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    xASSERT( (ulIntFlags & ~(
                            INT_RDA     |
                            INT_THRE    |
                            INT_RLS     |
                            INT_MODEM   |
                            INT_CTS     |
                            INT_ABEO    |
                            INT_ABTO
                    )
             ) == 0);

    // DLAB MUST be zero.
    //xHWREG(ulBase + LCR) &= ~LCR_DLAB;

    // Clear interrupt control bit.
    xHWREG(ulBase + IER) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! \brief  Get uart interrupt status.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \return The interrupt status which consist of the logical OR the following value:
//!              - \ref INT_RDA
//!              - \ref INT_THRE
//!              - \ref INT_RLS
//!              - \ref INT_MODEM
//!              - \ref INT_CTS
//!              - \ref INT_ABEO
//!              - \ref INT_ABTO
//!
//
//*****************************************************************************
unsigned long UARTIntStatusGet(unsigned long ulBase)
{

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    // Read status register.
    return xHWREG(ulBase + IIR);
}

//*****************************************************************************
//
//! \brief  Check UART Interrupt Flag.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulIntFlags is the interrupt flag to be checked.
//!              which can be one of the following value:
//!              - \ref INT_RDA
//!              - \ref INT_THRE
//!              - \ref INT_RLS
//!              - \ref INT_MODEM
//!              - \ref INT_CTS
//!              - \ref INT_ABEO
//!              - \ref INT_ABTO
//!
//! \return
//!         - xtrue  The checked flag has been set.
//!         - xflase The checked flag has not been set.
//
//*****************************************************************************
xtBoolean UARTIntStatusCheck(unsigned long ulBase, unsigned long ulIntFlags)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    xASSERT( (ulIntFlags & ~(
                                 INT_FLAG_RLS  |
                                 INT_FLAG_RDA  |
                                 INT_FLAG_CTI  |
                                 INT_FLAG_THRE |
                                 INT_FLAG_MODEM|
                                 INT_FLAG_ABEO |
                                 INT_FLAG_ABTO
                            )
             ) == 0);

    switch(ulIntFlags)
    {
        case INT_FLAG_ABEO:
        case INT_FLAG_ABTO:
        case INT_FLAG_ABEO | INT_FLAG_ABTO:
            {
                if(xHWREG(ulBase + IIR) & ulIntFlags)
                {
                    return (xtrue);
                }
                else
                {
                    return (xfalse);
                }
            }
        case INT_FLAG_RLS   :
        case INT_FLAG_RDA   :
        case INT_FLAG_CTI   :
        case INT_FLAG_THRE  :
        case INT_FLAG_MODEM :
            {
                ulTmpReg = xHWREG(ulBase + IIR);

                // Is there a pending interrupt?
                if(ulTmpReg & IIR_INT_STAT)      // No
                {
                    return (xfalse);
                }
                else
                {
                    ulTmpReg = (ulTmpReg & BIT_MASK(32, 3, 1)) >> 1;
                    if (ulTmpReg == ulIntFlags)
                    {
                        return (xtrue);
                    }
                    else
                    {
                        return (xfalse);
                    }
                }
            }
        default:                                 // Error
            {
                while (1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Clear interrupt flag.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulFlags is the Modem status flag that you want to check.
//!              This value must be logical OR of the following value:
//!              - \ref INT_ABEO
//!              - \ref INT_ABTO
//!
//! \return None.
//
//*****************************************************************************
void UARTIntFlagClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );
    xASSERT( (ulIntFlags & ~(INT_ABEO | INT_ABTO)) == 0);

    switch(ulIntFlags)
    {
        case INT_ABEO:
        case INT_ABTO:
        case INT_ABEO | INT_ABTO:
            {
                xHWREG(ulBase + ACR) |= ulIntFlags;
                break;
            }

        default:                         // Error
            {
                while(1);
            }
    }
}

//*****************************************************************************
//
//! \brief  Configure uart FIFO.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulCfg is the parameters to configure FIFO.
//!              which can be the OR of the following value:
//!              - \ref FIFO_CFG_FIFO_EN
//!              - \ref FIFO_CFG_FIFO_DIS
//!              - \ref FIFO_CFG_RX_FIFO_RESET
//!              - \ref FIFO_CFG_TX_FIFO_RESET
//!              - \ref FIFO_CFG_DMA_EN
//!              - \ref FIFO_CFG_DMA_DIS
//!              - \ref FIFO_CFG_RX_TRI_LVL_0
//!              - \ref FIFO_CFG_RX_TRI_LVL_1
//!              - \ref FIFO_CFG_RX_TRI_LVL_2
//!              - \ref FIFO_CFG_RX_TRI_LVL_3
//!
//! \return None.
//
//*****************************************************************************
void UARTFIFOCfg(unsigned long ulBase, unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    xASSERT( (ulCfg & ~(
                             FIFO_CFG_FIFO_EN       |
                             FIFO_CFG_FIFO_DIS      |
                             FIFO_CFG_RX_FIFO_RESET |
                             FIFO_CFG_TX_FIFO_RESET |
                             FIFO_CFG_DMA_EN        |
                             FIFO_CFG_DMA_DIS       |
                             FIFO_CFG_RX_TRI_LVL_0  |
                             FIFO_CFG_RX_TRI_LVL_1  |
                             FIFO_CFG_RX_TRI_LVL_2  |
                             FIFO_CFG_RX_TRI_LVL_3
                         )
             ) == 0);

    // Configure FIFO
    ulTmpReg = xHWREG(ulBase + FCR);
    ulTmpReg &= ((~ulCfg) >> 16);
    ulTmpReg |= (ulCfg & 0xFFFF);
    xHWREG(ulBase + FCR) = ulTmpReg;
}

//*****************************************************************************
//
//! \brief  Start transmit function.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \return None.
//
//*****************************************************************************
void UARTTransStart(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    xHWREG(ulBase + TER) |= TER_TX_EN;
}

//*****************************************************************************
//
//! \brief  Stop transmit function.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \return None.
//
//*****************************************************************************
void UARTTransStop(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    xHWREG(ulBase + TER) &= ~TER_TX_EN;
}

//*****************************************************************************
//
//! \brief  Get UART status.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \return The status of uart, which consist of the logical OR of the following
//!         value:
//!              - \ref RX_FIFO_NOT_EMPTY
//!              - \ref OVERRUN_ERR
//!              - \ref PARITY_ERR
//!              - \ref FRAMING_ERR
//!              - \ref BREAK_INT
//!              - \ref TX_FIFO_EMPTY
//!              - \ref TX_EMPTY
//!              - \ref RX_FIFO_ERR
//
//*****************************************************************************
unsigned long UARTStatGet(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );

    return( xHWREG(ulBase + LSR) );
}

//*****************************************************************************
//
//! \brief  Check UART status flag.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulFlags is the checked flag, which consist of the following
//!              value:
//!              - \ref RX_FIFO_NOT_EMPTY
//!              - \ref OVERRUN_ERR
//!              - \ref PARITY_ERR
//!              - \ref FRAMING_ERR
//!              - \ref BREAK_INT
//!              - \ref TX_FIFO_EMPTY
//!              - \ref TX_EMPTY
//!              - \ref RX_FIFO_ERR
//!
//! \return
//!         - xtrue  The checked flag has been set.
//!         - xflase The checked flag has not been set.
//
//*****************************************************************************
xtBoolean UARTStatCheck(unsigned long ulBase, unsigned long ulFlags)
{

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );
    xASSERT( (ulFlags & ~(
                              RX_FIFO_NOT_EMPTY |
                              OVERRUN_ERR       |
                              PARITY_ERR        |
                              FRAMING_ERR       |
                              BREAK_INT         |
                              TX_FIFO_EMPTY     |
                              TX_EMPTY          |
                              RX_FIFO_ERR
                         )
             ) == 0);

    if(xHWREG(ulBase + LSR) & ulFlags)
    {
        return (xtrue);
    }
    else
    {
        return (xfalse);
    }
}

//*****************************************************************************
//
//! \brief  Configure IrDA.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulCfg is the checked flag, which consist of the OR of following
//!              value:
//!              - \ref IRDA_INV_EN
//!              - \ref IRDA_INV_DIS
//!              - \ref IRDA_FIX_PULSE_DIS
//!              - \ref IRDA_FIX_PULSE_2
//!              - \ref IRDA_FIX_PULSE_4
//!              - \ref IRDA_FIX_PULSE_8
//!              - \ref IRDA_FIX_PULSE_16
//!              - \ref IRDA_FIX_PULSE_32
//!              - \ref IRDA_FIX_PULSE_64
//!              - \ref IRDA_FIX_PULSE_128
//!              - \ref IRDA_FIX_PULSE_256
//!
//! \return None.
//!
//! \note   This function is only suit for UART0/2/3.
//
//*****************************************************************************
void UARTIrDACfg(unsigned long ulBase, unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) ||
            (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) );
    xASSERT( (ulCfg & ~(
                           IRDA_INV_EN        |
                           IRDA_INV_DIS       |
                           IRDA_FIX_PULSE_DIS |
                           IRDA_FIX_PULSE_2   |
                           IRDA_FIX_PULSE_4   |
                           IRDA_FIX_PULSE_8   |
                           IRDA_FIX_PULSE_16  |
                           IRDA_FIX_PULSE_32  |
                           IRDA_FIX_PULSE_64  |
                           IRDA_FIX_PULSE_128 |
                           IRDA_FIX_PULSE_256
                         )
             ) == 0);


    // Configure IrDA Invert, Fixed Pulse width.
    ulTmpReg = xHWREG(ulBase + ICR);
    ulTmpReg &= ((~ulCfg) >> 16);
    ulTmpReg |= (ulCfg & 0xFFFF);
    xHWREG(ulBase + ICR) = ulTmpReg;

}

//*****************************************************************************
//
//! \brief  Enable IrDA Function.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \return None.
//!
//! \note   This function is only suit for UART0/2/3.
//
//*****************************************************************************
void UARTIrDAEnable(unsigned long ulBase)
{
    xHWREG(ulBase + ICR) |= ICR_IRDA_EN;
}

//*****************************************************************************
//
//! \brief  Disable IrDA Function.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \return None.
//!
//! \note   This function is only suit for UART0/2/3.
//
//*****************************************************************************
void UARTIrDADisable(unsigned long ulBase)
{
    xHWREG(ulBase + ICR) &= ~ICR_IRDA_EN;
}

//*****************************************************************************
//
//! \brief  Configure UART.
//!         This function configure uart baud, data length, stop bit, parity.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART0_BASE
//!              - \ref UART1_BASE
//!              - \ref UART2_BASE
//!              - \ref UART3_BASE
//!
//! \param  [in] ulBaud is the target baud.
//!
//! \param  [in] ulCfg is uart configure parameters. which can be the logical
//!              OR of the following value:
//!              - \ref UART_CFG_LEN_5_BIT
//!              - \ref UART_CFG_LEN_6_BIT
//!              - \ref UART_CFG_LEN_7_BIT
//!              - \ref UART_CFG_LEN_8_BIT
//!              - \ref UART_CFG_STOP_1_BIT
//!              - \ref UART_CFG_STOP_2_BIT
//!              - \ref UART_CFG_PARITY_NONE
//!              - \ref UART_CFG_PARITY_ODD
//!              - \ref UART_CFG_PARITY_EVEN
//!              - \ref UART_CFG_PARITY_1
//!              - \ref UART_CFG_PARITY_0
//!              - \ref UART_CFG_BREAK_EN
//!              - \ref UART_CFG_BREAK_DIS
//!
//! \return None.
//
//*****************************************************************************
void UARTCfg(unsigned long ulBase, unsigned long ulBaud, unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT((ulBase == UART0_BASE) || (ulBase == UART1_BASE) ||
            (ulBase == UART2_BASE) || (ulBase == UART3_BASE) );
    xASSERT( (ulCfg & ~(
                           UART_CFG_LEN_5_BIT   |
                           UART_CFG_LEN_6_BIT   |
                           UART_CFG_LEN_7_BIT   |
                           UART_CFG_LEN_8_BIT   |
                           UART_CFG_STOP_1_BIT  |
                           UART_CFG_STOP_2_BIT  |
                           UART_CFG_PARITY_NONE |
                           UART_CFG_PARITY_ODD  |
                           UART_CFG_PARITY_EVEN |
                           UART_CFG_PARITY_1    |
                           UART_CFG_PARITY_0    |
                           UART_CFG_BREAK_EN    |
                           UART_CFG_BREAK_DIS
                       )
             ) == 0);

    // Configure UART Data length, Parity, stop bit, break.
    ulTmpReg = xHWREG(ulBase + LCR);
    ulTmpReg &= ((~ulCfg) >> 16);
    ulTmpReg |= (ulCfg & 0xFFFF);
    xHWREG(ulBase + LCR) = ulTmpReg;

    // Configure UART baud
    UartSetDivisors(ulBase, ulBaud);
}

//*****************************************************************************
//
//! \brief  Configure Modem function.
//!         This function configure uart modem.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART1_BASE
//!
//! \param  [in] ulCfg is uart modem configure parameters. which can be the logical
//!              OR of the following value:
//!              - \ref LOOPBACK_MODE_EN
//!              - \ref LOOPBACK_MODE_DIS
//!              - \ref AUTO_RTS_EN
//!              - \ref AUTO_RTS_DIS
//!              - \ref AUTO_CTS_EN
//!              - \ref AUTO_CTS_DIS
//!
//! \return None.
//
//*****************************************************************************
void UARTModemCfg(unsigned long ulBase, unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT(ulBase == UART1_BASE);
    xASSERT( (ulCfg & ~(
                       LOOPBACK_MODE_EN  | LOOPBACK_MODE_DIS |
                       AUTO_RTS_EN       | AUTO_RTS_DIS      |
                       AUTO_CTS_EN       | AUTO_CTS_DIS
                       )
             ) == 0);

    // Configure UART Modem.
    ulTmpReg = xHWREG(ulBase + MCR);
    ulTmpReg &= ((~ulCfg) >> 16);
    ulTmpReg |= (ulCfg & 0xFFFF);
    xHWREG(ulBase + MCR) = ulTmpReg;

}

//*****************************************************************************
//
//! \brief  Configure RS485 function.
//!         This function configure uart rs485.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART1_BASE
//!
//! \param  [in] ulCfg is uart modem configure parameters. which can be the logical
//!              OR of the following value:
//!              - \ref RS485_NMM_DIS
//!              - \ref RS485_NMM_EN
//!              - \ref RS485_RX_EN
//!              - \ref RS485_RX_DIS
//!              - \ref RS485_AUTO_ADDR_EN
//!              - \ref RS485_AUTO_ADDR_DIS
//!              - \ref RS485_AUTO_DIR_DIS
//!              - \ref RS485_AUTO_DIR_RTS
//!              - \ref RS485_AUTO_DIR_DTR
//!              - \ref RS485_AUTO_DIR_INV_EN
//!              - \ref RS485_AUTO_DIR_INV_DIS
//!
//! \return None.
//
//*****************************************************************************
void UARTRS485Cfg(unsigned long ulBase, unsigned long ulCfg)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT(ulBase == UART1_BASE);
    xASSERT( (ulCfg & ~(
                            RS485_NMM_DIS         | RS485_NMM_EN          |
                            RS485_RX_EN           | RS485_RX_DIS          |
                            RS485_AUTO_ADDR_EN    | RS485_AUTO_ADDR_DIS   |
                            RS485_AUTO_DIR_DIS    |
                            RS485_AUTO_DIR_RTS    |
                            RS485_AUTO_DIR_DTR    |
                            RS485_AUTO_DIR_INV_EN | RS485_AUTO_DIR_INV_DIS
                       )
             ) == 0);



    // Configure RS485
    ulTmpReg = xHWREG(ulBase + RS485CTRL);
    ulTmpReg &= ((~ulCfg) >> 16);
    ulTmpReg |= (ulCfg & 0xFFFF);
    xHWREG(ulBase + RS485CTRL) = ulTmpReg;
}

//*****************************************************************************
//
//! \brief  Configure RS485 slave address.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART1_BASE
//!
//! \param  [in] uladdr is rs485 slave address.
//!
//! \return None.
//
//*****************************************************************************
void UARTRS485AddrSet(unsigned long ulBase, unsigned long ulAddr)
{
    // Check input parameters.
    xASSERT(ulBase == UART1_BASE);
    xASSERT((ulAddr & ~RS485ADRMATCH_ADRMATCH_M) == 0);

    xHWREG(ulBase + ADRMATCH) = (ulAddr & RS485ADRMATCH_ADRMATCH_M);
}

//*****************************************************************************
//
//! \brief  Configure RS485 Delay Time value.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART1_BASE
//!
//! \param  [in] uladdr is rs485 delay time value.
//!
//! \return None.
//
//*****************************************************************************
void UARTRS485DlyTimeSet(unsigned long ulBase, unsigned long ulVal)
{
    // Check input parameters.
    xASSERT(ulBase == UART1_BASE);
    xASSERT((ulVal & ~RS485DLY_DLY_M) == 0);

    xHWREG(ulBase + RS485DLY) = (ulVal & RS485DLY_DLY_M);
}

//*****************************************************************************
//
//! \brief  Get Modem status.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART1_BASE
//!
//! \return The Modem status value.
//
//*****************************************************************************
unsigned long UARTModemStatGet(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(ulBase == UART1_BASE);

    return (xHWREG(ulBase + MSR));
}

//*****************************************************************************
//
//! \brief  Check Modem status Flag.
//!
//! \param  [in] ulBase is the uart module base address.
//!              This value can be one of the following value:
//!              - \ref UART1_BASE
//!
//! \param  [in] ulFlags is the Modem status flag that you want to check.
//!              This value must be logical OR of the following value:
//!              - \ref xxx
//!
//! \return
//!         - xtrue  The checked flag has been set.
//!         - xflase The checked flag has not been set.
//
//*****************************************************************************
xtBoolean UARTModemStatCheck(unsigned long ulBase, unsigned long ulFlags)
{

    // Check input parameters.
    xASSERT(ulBase == UART1_BASE);

    // Check Status Bit.
    if(xHWREG(ulBase + MSR) & ulFlags)           // Set
    {
        return (xtrue);
    }
    else                                         // Unset
    {
        return (xfalse);
    }
}

