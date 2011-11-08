//*****************************************************************************
//
//! \file PWM_Output.c
//! \brief PWM output function test.
//! \version 1.0
//! \date 10/27/2011
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
#include "xhw_pwm.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xuart.h"
#include "xpwm.h"

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
//! \brief PWM output function example. 
//!
//! \return None.
//
//*****************************************************************************
void PWM_Output()
{
    //
    // Initionalize system clock and I/O port.
    //
    IOInit();
	
    PrintLine( "*** Cox PWM example ***" );

    //
    // Set GPIO Pin as PWM and enable PWM
    //
    xSPinTypePWM( PWM5, PE5 );
	xSysCtlPeripheralEnable( xSYSCTL_PERIPH_PWMB );
                                             
    //
    // Set invert, dead zone and mode
    //
    xPWMInitConfigure( xPWMB_BASE, xPWM_CHANNEL5, xPWM_TOGGLE_MODE | 
	                            xPWM_OUTPUT_INVERTER_DIS | xPWM_DEAD_ZONE_DIS );
	
    // Set CNR, Prescale and Divider
    xPWMFrequencyConfig( xPWMB_BASE, xPWM_CHANNEL5, 0x3FF1111 );
	
    //    
    // Set CMR
    //
    xPWMDutySet( xPWMB_BASE, xPWM_CHANNEL5, 40 );
	
	//    
    // Set output enable
    //
    xPWMOutputEnable( xPWMB_BASE, xPWM_CHANNEL5 );   
	
    // Set interrupt call back 
    xPWMIntCallbackInit( xPWMB_BASE, user_Callback );
	
    //
    // PWM output interrupt enable
    //
    xPWMIntEnable( xPWMB_BASE, xPWM_CHANNEL5, xPWM_INT_PWM );
	
    //
    // NVIC interrupt enable
    //
    xIntEnable( xINT_PWMB );
	
    //    
    // start pwm
    //
    xPWMStart( xPWMB_BASE, xPWM_CHANNEL5 );
}

//*****************************************************************************
//! \breif PWM interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback( void *pvCBData, unsigned long ulEvent, 
							         unsigned long ulMsgParam, void *pvMsgData )                                        
{
    //
    // Change the PWM's duty
    //
    static unsigned long ultemp = 0;
    ultemp += 5;
    if ( ultemp > 100 )
         ultemp = 10;
	
    xPWMDutySet( xPWMB_BASE, xPWM_CHANNEL5, ultemp );    
    
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
