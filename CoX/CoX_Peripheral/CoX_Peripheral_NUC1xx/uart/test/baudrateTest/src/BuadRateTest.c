#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xhw_memmap.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xgpio.h"
#include "xhw_uart.h"
#include "xuart.h"

#define BAUDRATE  115200
#define CLK_SRC_M  0xF0FFFFFF 
#define CLK_DIV_M  0xFFFFF0FF

//
// 0x00000000: 12M
// 0x01000000: PLL, 48M
// 0x03000000: 22M
//
unsigned long clkSrcSel[3] = {0x00000000, 0x01000000, 0x03000000};
unsigned long clkSrc[3] = {12, 48, 22};
unsigned long clkDivSel[3][3] = {{1, 2, 4}, {1, 2, 16},{1, 2, 8}};

unsigned char send[] = "This is buadrate test for cox lib of NUC1xx.\r\n";
unsigned char info[] = "\r\n\r\n--------------NUC1xx.UART.BAUDRATE TEST--------------- \r\n\r\n";
#define SENDNUM  sizeof(send)

void ItemPrint(int i, int j);

void BuadRateTest()
{
    unsigned long ulTemp1, ulBuad, ulConfig;
    int i, j;
   
    SysCtlKeyAddrUnlock();
    xHWREG(SYSCLK_PWRCON) |= (SYSCLK_PWRCON_XTL12M_EN | SYSCLK_PWRCON_OSC22M_EN);
    SysCtlKeyAddrLock();
    
    //
    // Config 8 bit word length, 1 stop bit, 
    // and none parity bit, receive FIFO 1 byte.
    //
    ulTemp1 = (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    SysCtlDelay(10000);

    xSPinTypeUART(UART0RX,PB0);
    xSPinTypeUART(UART0TX,PB1);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    UARTConfigSetExpClk(UART0_BASE, BAUDRATE, (UART_CONFIG_WLEN_8 | 
                                             UART_CONFIG_STOP_ONE | 
                                               UART_CONFIG_PAR_NONE));

    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
 
    UARTBufferWrite(UART0_BASE, info, sizeof(info)); 

    while(!UARTFIFOTxIsEmpty(UART0_BASE));     
    SysCtlDelay(10000);

    //
    // Test in different Clock Source and Clock Divider.
    //
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            SysCtlKeyAddrUnlock();

            //
            // Config the PLL register to get 48M clock.
            //
            if(i == 1)
            {
                xHWREG(SYSCLK_PLLCON) = 0x0000C22E;  //48M
            }

            //
            // Select the Clock Source, Config Divider.
            //
            xHWREG(SYSCLK_CLKSEL1) &= CLK_SRC_M;
            xHWREG(SYSCLK_CLKSEL1) |= clkSrcSel[i];
            xHWREG(SYSCLK_CLKDIV)  &= CLK_DIV_M;
            xHWREG(SYSCLK_CLKDIV)  |= ((clkDivSel[i][j] - 1)<<8);
            SysCtlKeyAddrLock();
            
            SysCtlDelay(10000);

            //
            // Config UART0, the baudrate will be set in different
            // mode decided by UART0 clock.
            //
            UARTConfigSetExpClk(UART0_BASE, BAUDRATE, ulTemp1);
            UARTConfigGetExpClk(UART0_BASE, &ulBuad, &ulConfig);
            ItemPrint(i, j);
            UARTBufferWrite(UART0_BASE, send, SENDNUM);

            //
            // Wait until the Tx FIFO is Empty.
            //
            while(!UARTFIFOTxIsEmpty(UART0_BASE));
            SysCtlDelay(10000);
        }
    }
}

void ItemPrint(int i, int j)
{
    unsigned char c[17] = "1.1 12M, 2div: \r\n";
    c[0] = i + 1 + '0';
    c[2] = j + 1 + '0';
    c[4] = clkSrc[i]/10 + '0';
    c[5] = clkSrc[i]%10 + '0';
    if(clkDivSel[i][j]/10 != 0)  
        c[8] = clkDivSel[i][j]/10 + '0';
    c[9] = clkDivSel[i][j]%10 + '0';
    UARTBufferWrite(UART0_BASE, c, 17);
}

