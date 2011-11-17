//*****************************************************************************
//
//! @page di_ad7417arz_testcase di_ad7417arz compare and int mode test
//!
//! File: @ref AD7417test2.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the di_ad7417arz sub component.<br><br>
//! - \p Board: NUC140 & AD7417ARZ board <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_di_ad7417arz_Comod
//! .
//! \file AD7417test2.c
//! \brief di_ad7417 test source file
//! \brief di_ad7417 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_ad7417.h"
#include "ad7417.h"

//*****************************************************************************
//
//!\page test_di_ad7417arz_Comod test_di_ad7417arz_Comod
//!
//!<h2>Description</h2>
//!Test di_ad7417arz compare and int mode. <br>
//!
//
//*****************************************************************************

//
// Callback funciton
//
static unsigned long ReadOperation(void *pvCBData, unsigned long ulEvent,
                                   unsigned long ulMsgParam, void *pvMsgData)
{
    AD7417TempReadLDC();
    TestEmitToken('a');
    return 0;
}

//*****************************************************************************
//
//! Declaration of the uart configuration function
//
//*****************************************************************************
void UART0Configuration(void);
void PrintN(unsigned long n);

//*****************************************************************************
//
//! \brief Get the Test description of di_ad7417arz001 compare mode test.
//!
//! \return the desccription of the di_ad7417arz001 test.
//
//*****************************************************************************
static char* di_ad7417arz001GetTest(void)
{
    return "ad7417arz [001]: ad7417 compare and int mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of di_ad7417arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001Setup(void)
{
    //
    //Set the external 12MHZ clock as system clock 
    //
    xSysCtlClockSet(12000000, SYSCLK_PWRCON_XTL12M_EN | xSYSCTL_OSC_MAIN);
    
    //
    // AD7417 device init
    //
    AD7417Init(10000, AD7417_ShutDown_Disable | AD7417_Triger_Disable); 
    
    UART0Configuration();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of di_ad7417arz001 test.
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001TearDown(void)
{
    AD7417DeInit();
    AD7417OTIntDisable();
}

//*****************************************************************************
//
//! \brief ad7417arz 001 test execute main body.
//!
//! First set the OTI as compare output mode ,then turned to Int mode.When the 
//! temperature up to 30 centigrade, the OTI pin will be low level ,then clear 
//! the ucFlag to end of the while and set the OTI as Int mode. 
//!
//! \return None.
//
//*****************************************************************************
static void di_ad7417arz001Execute(void)
{
    unsigned long ulTemp;
    unsigned char ucFlag = 1;
     int i;
    
    //
    // Configure the setpoint register
    //
    AD7417LowLimitSetLong(26);
    AD7417UpLimitSetLong(26);
    
    //
    // Config the OTI connected pin as input pin
    //
    xGPIOSPinTypeGPIOInput(AD7417_OTI_PIN);
    
    //
    // Config the OTI active level low , Fault QUEUE is 1
    // OTI compare mode, temperature channel
    //
    
    AD7417TempConfig(AD7417_OTI_CMP | AD7417_OTI_ACTIVE_LOW |
                     AD7417_FAULTQUE_1 | AD7417_TEMP_CHANNEL);
    while(ucFlag)
    {
        ulTemp = AD7417TempReadLDC();
        for(i = 0; i < 10000; i++);
        PrintN(ulTemp);
        ulTemp = xGPIOSPinRead(AD7417_OTI_PIN);
        if(!ulTemp)
        {
            ucFlag = 0;
            
            //
            // Change the mode to int mode,the 
            //
            AD7417TempConfig(AD7417_OTI_INT);
            
            //
            // Change the UpLimit TO 31 C to prevent active 
            //
            AD7417UpLimitSetLong(26);
        }       
    }
    
    //
    // Change to INT mode 
    //
    AD7417TempConfig(AD7417_OTI_INT | AD7417_OTI_ACTIVE_LOW |
                     AD7417_FAULTQUE_1 | AD7417_TEMP_CHANNEL);
    
    AD7417OTIntEnable();
    AD7417OTIntCallbackInit(ReadOperation);
    ulTemp = AD7417TempReadLDC();
    for(i = 0; i < 10000; i++);
    PrintN(ulTemp);
    TestAssertQ("a", "OTI INT mode test fail");
}

//
// di_ad7417arz register test case struct.
//
const tTestCase sTestdi_ad7417arz_Comod = {
            di_ad7417arz001GetTest,
            di_ad7417arz001Setup,
            di_ad7417arz001TearDown,
            di_ad7417arz001Execute
};

//
// xi2c test suits.
//
const tTestCase * const psPatternDI_AD7417ARZ002[] =
{
    &sTestdi_ad7417arz_Comod,
    0
};


//*****************************************************************************
//
//! \biref uart0 configre 
//!
//! \return  none
//
//*****************************************************************************
void UART0Configuration(void)
{
  
     xSPinTypeUART(UART0Rx,PB0);
     xSPinTypeUART(UART0Tx,PB1);

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
//! \brief Prints a decimal unsigned number.
//!
//! \param n is the number to be printed
//!
//! \details Prints a decimal unsigned number.
//!
//! \return None.
//
//*****************************************************************************
void PrintN(unsigned long n)
{
    char buf[16], *p;

    if (n == 0)
    {

        while((xHWREG(UART0_BASE + UART_FSR) & (0x400000))!=0x400000);
         //
         // Write this character to the transmit FIFO.
         //
         xHWREG(UART0_BASE + UART_THR) = '0';
    }
    else
    {
        p = buf;
        while (n != 0)
        {
            *p++ = (n % 10) + '0';
            n /= 10;
        }

        while (p > buf)
        {

            while((xHWREG(UART0_BASE + UART_FSR) & (0x400000))!=0x400000);
             //
             // Write this character to the transmit FIFO.
             //
             xHWREG(UART0_BASE + UART_THR) = *--p;           
        }
    }
}