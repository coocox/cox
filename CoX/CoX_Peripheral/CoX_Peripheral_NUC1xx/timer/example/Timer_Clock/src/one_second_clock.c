//*****************************************************************************
//
//! \file one_second_clock.c
//! \brief Use the timer to make a one second clock.
//! \date 9/20/2011
//! \author CooCox
//! 
//! The timer source select external 12M hz crystal oscillator, the TCMP register
//! set to oxffff, the prescale register value is 12M/0x1ffff = 92
//! 
//! \copy
//
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_gpio.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_timer.h"
#include "xhw_uart.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xtimer.h"
#include "xuart.h"

//*****************************************************************************
//
//! \biref function declaration
//!
//! \return  none
//
//*****************************************************************************
void Print(char *pcMsg);
void UART0Configuration(void);

//*****************************************************************************
//
//! \biref The main example function
//!
//! \return  none
//
//*****************************************************************************
void OneSecondClock(void)
{
    //
    //Set the external 12MHZ clock as system clock 
    //
	SysCtlKeyAddrUnlock();
	xHWREG(SYSCLK_PWRCON) |= SYSCLK_PWRCON_XTL12M_EN;
    
    //
    // Set the timer clock
    //
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TMR0_S_EXT12M);
    
    UART0Configuration();
    
    // 
    // Enable tiemr0
    // 
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_TIMER0);  
    
    //
    // Clear the flag first
    //
    xTimerIntClear(TIMER0_BASE, 0, TIMER_INT_MATCH);
    while(xTimerIntStatus(TIMER0_BASE, 0, TIMER_INT_MATCH));
    
    // 
    // Config as One shot mode
    //        
    xTimerInitConfig(TIMER0_BASE, 0, TIMER_MODE_PERIODIC, 1000);
    xTimerPrescaleSet(TIMER0_BASE, 0, 91);
    xTimerMatchSet(TIMER0_BASE, 0, 0x1ffff);
    xTimerIntEnable(TIMER0_BASE, 0, TIMER_INT_MATCH);
    
    //
    // Start the timer
    //
    xTimerStart(TIMER0_BASE, 0);
        
    //
    // One shot mode test.
    //
    while(1)
    {       
        //
        // wait until the timer data register reach equel to compare register
        //
        while(!xTimerIntStatus(TIMER0_BASE, 0, TIMER_INT_MATCH));
        Print("one second has gone...");
        Print("\r\n");
        xTimerIntClear(TIMER0_BASE, 0, TIMER_INT_MATCH);
    }  
    

}

//*****************************************************************************
//
//! \biref uart0 configre 
//!
//! \return  none
//
//*****************************************************************************
void UART0Configuration(void)
{
  
	xSPinTypeUART(U0RX,PB0);
	xSPinTypeUART(U0TX,PB1);

	//xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

	xHWREG(UART0_BASE + UART_FCR) |= 0x6;
	xHWREG(UART0_BASE + UART_FCR) &= ~(0xF0);
	xHWREG(UART0_BASE + UART_FCR) |= 0;

	xHWREG(UART0_BASE + UART_LCR) = 3;
	xHWREG(UART0_BASE + UART_BAUD) = 0x3F000066;

	SysCtlDelay(10000);
}

//*****************************************************************************
//
//! \breif uart send function
//
//! \return none
//
//*****************************************************************************
void Print(char *pcMsg)
{
    unsigned char ch;
    while (*pcMsg != '\0')
    {
        //
        // Put a character in the output buffer.
        //
        ch = *pcMsg++;

        while((xHWREG(UART0_BASE + UART_FSR) & (0x400000))!=0x400000);
	    //
	   // Write this character to the transmit FIFO.
	    //
	    xHWREG(UART0_BASE + UART_THR) = ch;
    }
}