/******************************************************************************
 * \file    UART_Example_Basic.c
 * \brief   Show how to use uart to print string via serial port.
 * 
******************************************************************************/

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xdebug.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"

#define TICK_SLOW              ((unsigned long)0xFFFFF)

#define UART_ID    0
//#define UART_ID    1

static volatile unsigned long Passed = 0;

void UART_Example_Basic(void);

unsigned long UserUARTHandler(void *pvCBData, unsigned long ulEvent,
                              unsigned long ulMsgParam, void *pvMsgData)
{
    if( UARTIntStatusCheck(UART0_BASE, INT_ABEO | INT_ABTO) )
    {
        UARTIntFlagClear(UART0_BASE, INT_ABEO | INT_ABTO);
        Passed = 1;
    }
    else
    {
        while(1);
    }

    return (0);
}

void UART_Example_Basic(void)
{ 

    /********************** Configure System clock *************************/
    SysCtlClockSet(100000000, SYSCTL_OSC_INT | SYSCTL_XTAL_12_MHZ);
    SysCtlDelay(TICK_SLOW);
    
    /********************** Configure GPIO Port ****************************/      
#if (UART_ID == 0)
    // 1: Enable GPIO Power and Clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // 2: Map GPIO Pin
    //    UART0 TX --> PA2
    //    UART0 RX --> PA3
    xSPinTypeUART(UART0TX, PA2);
    xSPinTypeUART(UART0RX, PA3);
#elif (UART_ID == 1)
    // 1: Enable GPIO Power and Clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // 2: Map GPIO Pin
    //    UART1 TX --> PC0
    //    UART1 RX --> PC1
    xSPinTypeUART(UART1TX, PC0);
    xSPinTypeUART(UART1RX, PC1);
#endif  

    /********************** Configure UART *********************************/
    // 1: Enable UART0 Power and clock
#if (UART_ID == 0)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTCfg(UART0_BASE, 9600, UART_CFG_LEN_8_BIT | UART_CFG_STOP_1_BIT |
            UART_CFG_PARITY_NONE | UART_CFG_BREAK_DIS);
    UARTFIFOCfg(UART0_BASE, FIFO_CFG_FIFO_EN | FIFO_CFG_RX_TRI_LVL_0);

    UARTIntEnable(UART0_BASE, INT_ABEO | INT_ABTO);
    UARTIntCallbackInit(UART0_BASE, UserUARTHandler);
    xIntEnable(xINT_UART0);
    xHWREG(UART0_BASE + ACR) |= ACR_START;
    while(Passed == 0);
    UARTStrSend(UART0_BASE, "\r\nHello world\r\n");
#elif (UART_ID == 1)
    // 1: Enable UART1 Power and clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    UARTCfg(UART1_BASE, 9600, UART_CFG_LEN_8_BIT | UART_CFG_STOP_1_BIT |
            UART_CFG_PARITY_NONE | UART_CFG_BREAK_DIS);
    UARTFIFOCfg(UART1_BASE, FIFO_CFG_FIFO_EN | FIFO_CFG_RX_TRI_LVL_0);

    UARTStrSend(UART1_BASE, "Hello world\r\n");
#endif

    while (1)
    {
        ;
    }
}
