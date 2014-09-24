#include "CoX.h"
#include "hw_uart.h"

//*****************************************************************************
//
// An array for uart callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnUARTHandlerCallbacks[4] = {0};

//*****************************************************************************
//
//! \internal
//! Checks a uart base address.
//!
//! \param ulBase is the base address of the uart port.
//!
//! This function determines if a uart port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef xDEBUG
static xtBoolean
UARTBaseValid(unsigned long ulBase)
{
    return((ulBase == UART0_BASE) ||
           (ulBase == UART1_BASE) ||
		   (ulBase == UART2_BASE) ||
		   (ulBase == UART3_BASE));
}
#endif

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
    if(g_pfnUARTHandlerCallbacks[0] != 0)
    {
        g_pfnUARTHandlerCallbacks[0](0, 0, 0, 0);
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
    if(g_pfnUARTHandlerCallbacks[1] != 0)
    {
        g_pfnUARTHandlerCallbacks[1](0, 0, 0, 0);
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
    if(g_pfnUARTHandlerCallbacks[2] != 0)
    {
        g_pfnUARTHandlerCallbacks[2](0, 0, 0, 0);
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
    if(g_pfnUARTHandlerCallbacks[3] != 0)
    {
        g_pfnUARTHandlerCallbacks[3](0, 0, 0, 0);
    }
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

    xASSERT(UARTBaseValid(ulBase));

    switch(ulBase)
    {
        case UART0_BASE:
            {
                //ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART0);
                break;
            }

        case UART1_BASE:
            {
                //ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART1);
                break;
            }

        case UART2_BASE:
            {
                //ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART2);
                break;
            }

        case UART3_BASE:
            {
                //ulPeriClk = SysCtlPeripheralClockGet(PCLKSEL_UART3);
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
    xASSERT(UARTBaseValid(ulBase));

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
    xASSERT(UARTBaseValid(ulBase));

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
    xASSERT(UARTBaseValid(ulBase));

    while(0 != *pStr)
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
    xASSERT(UARTBaseValid(ulBase));

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
    xASSERT(UARTBaseValid(ulBase));

    for(i = 0; i < ulLen; i++)
    {
        pBuf[i] = UARTByteRead(ulBase);
    }
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
    xASSERT(UARTBaseValid(ulBase));

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
    xASSERT(UARTBaseValid(ulBase));

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
    xASSERT(UARTBaseValid(ulBase));
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
    xASSERT(UARTBaseValid(ulBase));

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
    xASSERT(UARTBaseValid(ulBase));

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
    xASSERT(UARTBaseValid(ulBase));

    xHWREG(ulBase + TER) &= ~TER_TX_EN;
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
    xASSERT(UARTBaseValid(ulBase));
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
    xASSERT(UARTBaseValid(ulBase));
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
    xASSERT(UARTBaseValid(ulBase));
    xHWREG(ulBase + ICR) &= ~ICR_IRDA_EN;
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
//! \b xUART_CONFIG_WLEN_7, \b xUART_CONFIG_WLEN_6, and \b xUART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b xUART_CONFIG_STOP_1 and \b xUART_CONFIG_STOP_2 select one or two stop
//! bits (respectively).  \b xUART_CONFIG_PAR_NONE, \b xUART_CONFIG_PAR_EVEN,
//! \b xUART_CONFIG_PAR_ODD, \b xUART_CONFIG_PAR_ONE, and
//! \b xUART_CONFIG_PAR_ZERO select the parity mode (no parity bit,
//! even parity bit, odd parity bit, parity bit always one, and parity bit
//! always zero, respectively).
//!
//!
//! \return None.
//
//*****************************************************************************

void
xUARTConfigSet(unsigned long ulBase, unsigned long ulBaud, unsigned long ulConfig)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT(UARTBaseValid(ulBase));;
    xASSERT( (ulConfig & ~(
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
    ulTmpReg &= ((~ulConfig) >> 16);
    ulTmpReg |= (ulConfig & 0xFFFF);
    xHWREG(ulBase + LCR) = ulTmpReg;

    // Configure UART baud
    UartSetDivisors(ulBase, ulBaud);
}

//*****************************************************************************
//
//! \brief Receives a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.
//!
//! This function replaces the original UARTCharNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.  A \b -1 is returned if there are no characters present in the
//! receive FIFO.  The UARTCharsAvail() function should be called before
//! attempting to call this function.
//
//*****************************************************************************
long xUARTCharGetNonBlocking(unsigned long ulBase)
{
    xASSERT(UARTBaseValid(ulBase));
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
long xUARTCharGet(unsigned long ulBase)
{
    xASSERT(UARTBaseValid(ulBase));
	return UARTByteRead(ulBase);
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
//! This function replaces the original UARTCharNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit FIFO or \b false if there was no space available in the transmit
//! FIFO.
//
//*****************************************************************************
xtBoolean xUARTCharPutNonBlocking(unsigned long ulBase, unsigned char ucData)
{
    unsigned long ulTmpReg = 0;

    // Check input parameters.
    xASSERT(UARTBaseValid(ulBase));

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
void xUARTCharPut(unsigned long ulBase, unsigned char ucData)
{
    xASSERT(UARTBaseValid(ulBase));
	UARTByteWrite(ulBase, ucData);
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
//! - \b xUART_INT_ERROR - All Error interrupt
//! - \b xUART_INT_RT - Receive Timeout interrupt
//! - \b xUART_INT_TX - Transmit interrupt
//! - \b xUART_INT_RX - Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
void xUARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check input parameters.
    xASSERT(UARTBaseValid(ulBase));

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
void xUARTIntCallbackInit(unsigned long ulBase, xtEventCallback xtUARTCallback)
{
    // Check the parameters.
    xASSERT(UARTBaseValid(ulBase));
    xASSERT(pfnCallback != 0);

    // Register user call back function.
    switch(ulBase)
    {
        case UART0_BASE:
            {
                g_pfnUARTHandlerCallbacks[0] = xtUARTCallback;
                break;
            }

        case UART1_BASE:
            {
                g_pfnUARTHandlerCallbacks[1] = xtUARTCallback;
                break;
            }

        case UART2_BASE:
            {
                g_pfnUARTHandlerCallbacks[2] = xtUARTCallback;
                break;
            }

        case UART3_BASE:
            {
                g_pfnUARTHandlerCallbacks[3] = xtUARTCallback;
                break;
            }
    }
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
//! - \b xUART_INT_ERROR - All Error interrupt
//! - \b xUART_INT_RT - Receive Timeout interrupt
//! - \b xUART_INT_TX - Transmit interrupt
//! - \b xUART_INT_RX - Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
void xUARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    // Check input parameters.
    xASSERT(UARTBaseValid(ulBase));

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
//! \brief Gets current receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns the current state of each of the 4 receiver error
//! sources.  The returned errors are equivalent to the four error bits
//! returned via the previous call to UARTCharGet() or UARTCharGetNonBlocking()
//! with the exception that the overrun error is set immediately the overrun
//! occurs rather than when a character is next read.
//!
//! \return Returns a logical OR combination of the receiver error flags,
//! \b xUART_RXERROR_FRAMING, \b xUART_RXERROR_PARITY, \b xUART_RXERROR_BREAK
//! and \b xUART_RXERROR_OVERRUN.
//
//*****************************************************************************
unsigned long xUARTRxErrorGet(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(UARTBaseValid(ulBase));

    return( xHWREG(ulBase + LSR) );
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
void xUARTRxErrorClear(unsigned long ulBase)
{
    // Check input parameters.
    xASSERT(UARTBaseValid(ulBase));

    xHWREG(ulBase + LSR) |= xHWREG(ulBase + LSR);
}
