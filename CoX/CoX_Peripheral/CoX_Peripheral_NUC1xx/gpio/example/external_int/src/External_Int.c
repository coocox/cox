//*****************************************************************************
//
//! \file External_Int.c
//! \brief External interrupt test.
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
#include "xhw_sysctl.h"
#include "xhw_gpio.h"
#include "xhw_uart.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"

//*****************************************************************************
//
// Global variable.
//
//*****************************************************************************
static unsigned char ucflag = 0;

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

void External_Int( void )
{
    //
    // Initionalize system clock and I/O port.
    //
    IOInit();
	
    PrintLine( "*** Cox GPIO example ***" );
	
    //
    // Set GPIO port B pin 15 mode.
    //
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_15, xGPIO_DIR_MODE_IN );
    
    //
    // Set GPIO port C pin 12, 13 mode.
    //
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_12 | xGPIO_PIN_13, 
                                                      xGPIO_DIR_MODE_OUT );
	
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit( xGPIO_PORTB_BASE, xGPIO_PIN_15, user_Callback );
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable( xGPIO_PORTB_BASE, xGPIO_PIN_15, xGPIO_BOTH_EDGES );
    xIntEnable( INT_EINT1 );
    
    ucflag = 0;
    while (ucflag == 0);
}


//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData )                                        
{
    //PrintLine( "EINT1 Interrupt!" );
    xGPIOPinWrite( xGPIO_PORTC_BASE, xGPIO_PIN_12 | xGPIO_PIN_13, 0 );
    ucflag = 1;
    
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
IOInit( void )
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

