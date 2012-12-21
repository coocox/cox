//*****************************************************************************
//
//! \file Wakeup.c
//! \brief WDT wakeup function test.
//! \version 1.0
//! \date 10/21/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xcore.h"
#include "xdebug.h"
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xhw_uart.h"
#include "xhw_wdt.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "xwdt.h"

//*****************************************************************************
//
// Function protype.
//
//*****************************************************************************
void IOInit( void );
void IOPut( char ch );
static void Print( char *pcMsg );
static void PrintLine( char *pcMsg );
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
                                    unsigned long ulMsgParam, void *pvMsgData );

//*****************************************************************************
//
//! \brief  Wdt wakeup example.
//!
//! \return None.
//
//*****************************************************************************
void Wakeup(void) 
{
    //
    // Initionalize system clock and I/O port.
    //
    IOInit();

    PrintLine("*** Cox WDT example ***");

    //
    // Set WDT clock and interval time.
    //
    xWDTInit(xWDT_BASE, SYSCTL_PERIPH_WDG_S_INT10K, xWDT_INTERVAL_2_10T);

    //
    // Set WDT interrupt and initionalize callback.
    //
    xWDTIntCallbackInit(xWDT_BASE, user_Callback);
    
    //
    // Enable WDT wake up function.
    //
    xWDTFunctionEnable(xWDT_BASE, xWDT_WAKEUP_FUNCTION | xWDT_INT_FUNCTION);
    xIntEnable( xINT_WDT );
    
    //
    // Start WDT timer.
    //
    xWDTEnable( xWDT_BASE );
   
    //
    // Make chip enter into sleep state.
    //
    xSysCtlSleep();
    
    //
    // Interrupt wake up cpu.
    //
    xCPUwfi();

    PrintLine("cpu is waken up !");
}
 
//*****************************************************************************
//! \breif Wdt interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData )                                        
{ 
    //
    // Restart wdt timer.
    //
    xWDTRestart();
   
    return 0;
}

//*****************************************************************************
//
//! \brief Init uart to print.
//!
//! \param None
//!
//! \details uart config as (115200, 8 data bit, 1 stop bit , no partiy)
//!
//! \return None.
//
//*****************************************************************************
void 
IOInit(void)
{
    SysCtlKeyAddrUnlock();
    xHWREG( SYSCLK_PWRCON ) |= SYSCLK_PWRCON_XTL12M_EN;

    SysCtlDelay( 10000 );

    xSPinTypeUART( UART0RX, PB0 );
    xSPinTypeUART( UART0TX, PB1 );
    

    xSysCtlPeripheralReset( xSYSCTL_PERIPH_UART0 );
    xSysCtlPeripheralEnable( xSYSCTL_PERIPH_UART0 );
    SysCtlPeripheralClockSourceSet( SYSCTL_PERIPH_UART_S_EXT12M );

    UARTConfigSetExpClk( UART0_BASE, 115200, ( UART_CONFIG_WLEN_8 | 
                                               UART_CONFIG_STOP_ONE | 
                                               UART_CONFIG_PAR_NONE ) );

    UARTEnable( UART0_BASE, ( UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX ) );
}

//*****************************************************************************
//
//! \brief print a char.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
IOPut( char ch )
{
    unsigned char c;
    c = ch;
    while( ( xHWREG( UART0_BASE + UART_FSR ) & ( 0x800000 ) ) == 0x800000 );
    //
    // Write this character to the transmit FIFO.
    //
    xHWREG( UART0_BASE + UART_THR ) = c;
}

//*****************************************************************************
//
//! \brief Prints a line without final end-of-line.
//!
//! \param pcMsg is the message to print
//!
//! \details Prints a line without final end-of-line.
//!
//! \return None.
//
//*****************************************************************************
static void 
Print( char *pcMsg )
{
    while ( *pcMsg != '\0' )
    {
        IOPut( *pcMsg++ );
    }
}

//*****************************************************************************
//
//! \brief Prints a line.
//!
//! \param pcMsg is the message to print
//!
//! \details Prints a line.
//!
//! \return None.
//
//*****************************************************************************
static void 
PrintLine( char *pcMsg )
{
    Print( pcMsg );
    IOPut( '\r' );
    IOPut( '\n' );
}
