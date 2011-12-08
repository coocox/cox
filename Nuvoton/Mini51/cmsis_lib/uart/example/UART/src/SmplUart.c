//*****************************************************************************
//
//! \file SmplUART.c
//! \brief example of UART.
//! \version v1.02.003
//! \date 23. August 2011
//! \author NuMicro MCU Software Team
//! \copy
//!
//! COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************  

//*****************************************************************************
//
//! Include related header files  
//
//*****************************************************************************
#include "DrvUART.h"
#include "DrvGPIO.h"
#include "DrvSYS.h"


#define RXBUFSIZE 384

//*****************************************************************************
//
//! Global variables
//
//*****************************************************************************
volatile uint8_t comRbuf[RXBUFSIZE];
volatile uint16_t comRbytes = 0;        /* Available receiving bytes */
volatile uint16_t comRhead  = 0;
volatile uint16_t comRtail  = 0;
volatile int32_t g_bWait    = TRUE;

void UART_INT_HANDLE(uint32_t u32IntStatus);
void UART_FunctionTest(void);
//*****************************************************************************
//
//! \brief UART Test Sample. It sends the received data to HyperTerminal.
//!
//! \param  None  
//!
//! \return None  
//
//*****************************************************************************
void UartTest(void)
{
    STR_UART_T sParam;

    /* SYSCLK =>12Mhz*/
    UNLOCKREG();
    GCR->P5_MFP = (GCR->P5_MFP & 0x00FFFCFC) | 0x03;  /* P5.1 -> XTAL2, P5.0 -> XTAL1 */
    CLK->PWRCON_BITS.XTLCLK_EN = 1;
    /* Waiting for 12M Xtal stalble */
    DrvSYS_Delay(5000);

    /* Select UART Clock Source From 12Mhz*/
    DrvSYS_SelectIPClockSource(UART_CLK_SET, 0);

    /* Set UART Pin */
    DrvGPIO_SelectFunction(FUNC_UART_TX_P00);
    DrvGPIO_SelectFunction(FUNC_UART_RX_P01);


    /* UART Setting */
    sParam.u32BaudRate      = 115200;
    sParam.u8cDataBits      = DRVUART_DATABITS_8;
    sParam.u8cStopBits      = DRVUART_STOPBITS_1;
    sParam.u8cParity        = DRVUART_PARITY_NONE;
    sParam.u8cRxTriggerLevel= DRVUART_FIFO_1BYTES;
    sParam.u8TimeOut          = 0;

    /* Set UART Configuration */
    while(DrvUART_Open(UART_PORT0,&sParam) != E_SUCCESS);

    UART_FunctionTest();
}

//*****************************************************************************
//
//! \brief UART Callback function
//!
//! \param  u32IntStatus the interrrupt status.  
//!
//! \return None  
//
//*****************************************************************************
void UART_INT_HANDLE(uint32_t u32IntStatus)
{

    uint8_t bInChar[1]={0xFF};


    if(u32IntStatus & DRVUART_RDAINT)
    {

        /* Get all the input characters */
        while(UART0->ISR_BITS.RDA_IF==1)
        {
            /* Get the character from UART Buffer */
            DrvUART_Read(UART_PORT0,bInChar,1);

            if(bInChar[0] == '0')
            {
                g_bWait = FALSE;
            }

            /* Check if buffer full */
            if(comRbytes < RXBUFSIZE)
            {
                /* Enqueue the character */
                comRbuf[comRtail] = bInChar[0];
                comRtail = (comRtail == (RXBUFSIZE-1)) ? 0 : (comRtail+1);
                comRbytes++;
            }
        }
    }
    else if(u32IntStatus & DRVUART_THREINT)
    {

        uint16_t tmp;
        tmp = comRtail;
        if(comRhead != tmp)
        {
            bInChar[0] = comRbuf[comRhead];
            DrvUART_Write(UART_PORT0,bInChar,1);
            comRhead = (comRhead == (RXBUFSIZE-1)) ? 0 : (comRhead+1);
            comRbytes--;
        }
    }

}

//*****************************************************************************
//
//! \brief UART Function Test 
//!
//! \param  None  
//!
//! \return None  
//
//*****************************************************************************
void UART_FunctionTest(void)
{
    /* Enable Interrupt and install the call back function */
    DrvUART_EnableInt(UART_PORT0, (DRVUART_RLSINT | DRVUART_THREINT | DRVUART_RDAINT),UART_INT_HANDLE);
    while(g_bWait);

    /* Disable Interrupt */
    DrvUART_DisableInt(UART_PORT0,DRVUART_RLSINT | DRVUART_THREINT | DRVUART_RDAINT);
    g_bWait =TRUE;
}



//*****************************************************************************
//
//! (C) COPYRIGHT 2011 Nuvoton Technology Corp.
//
//*****************************************************************************