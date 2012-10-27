//*****************************************************************************
//
//! @page xacmp_testcase xacmp register test
//!
//! File: @ref xacmptest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xacmp sub component.<br><br>
//! - \p Board: NUC140 <br><br>
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
//! - \subpage test_xacmp_register
//! .
//! \file xacmptest.c
//! \brief xacmp test source file
//! \brief xacmp test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_acmp.h"
#include "xacmp.h"

//*****************************************************************************
//
//!\page test_xacmp_register test_xacmp_register
//!
//!<h2>Description</h2>
//!Test xacmp register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Comparator 0 Interrupt Handler.
//!
//! If users want to user the ACMP Interrupt Callback feature, Users should 
//! promise that the ACMP Handler in the vector table is CMPIntHandler.
//!
//! \return None.
//
//*****************************************************************************
void CMP_IRQHandler( void )
{
    TestAssert( 1 == ACMPIntStatus( ACMP_BASE, 0 ), 
               "xacmp API \"ACMPIntStatus()\" error!" );
    ACMPIntClear( ACMP_BASE, 0 );
    
    TestEmitToken( 'T' );
}

//*****************************************************************************
//
//! \brief  xacmp api comparator interrupt status test.
//!
//! \return None.
//
//*****************************************************************************
static void Int_Status( void )
{
    ACMPNegativeSrcSet( ACMP_BASE, 0, ACMP_ASRCN_REF );
    
    ACMPIntEnable( ACMP_BASE, 0 );
    xIntEnable( xINT_ACMP0 );
    
    if ( 1 == ACMPIntStatus( ACMP_BASE, 0 ) )
    {
        ACMPIntClear( ACMP_BASE, 0 );
        TestAssert( 1 == ACMPIntStatus( ACMP_BASE, 0 ), 
                   "xacmp API \"ACMPIntClear()\" error!" );
    }
    
    ACMPEnable( ACMP_BASE, 0 );
    
    TestAssertQBreak( "T", "xacmp interrupt function error!", 0xFFFFFFFF );
}

//*****************************************************************************
//
//! \brief xacmp001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xacmp001Execute( void )
{
    Int_Status( );
}

//*****************************************************************************
//
//! \brief Get the Test description of xacmp001 register test.
//!
//! \return the desccription of the xacmp001 test.
//
//*****************************************************************************
static char* xacmp001GetTest( void )
{
    return "xacmp, 001, xacmp register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xacmp001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xacmp001Setup( void )
{
    //
    // reset acmp 
    //
    SysCtlPeripheralReset( SYSCTL_PERIPH_ACMP );
    
    //
    // enable acmp clock 
    //
    SysCtlPeripheralEnable( SYSCTL_PERIPH_ACMP );
    
    //
    // config GPIO pin as ACMP function
    //
    xSPinTypeACMP( CMP0P, PC6 );
    xSPinTypeACMP( CMP0O, PB12 );
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xacmp001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xacmp001TearDown( void )
{
    
}

//
// xacmp001 register test case struct.
//
const tTestCase sTestXacmp001Register = {
    xacmp001GetTest,
    xacmp001Setup,
    xacmp001TearDown,
    xacmp001Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternXacmp[] =
{
    &sTestXacmp001Register,
    0
};
