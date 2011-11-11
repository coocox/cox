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
//! \brief  acmp api input source configure test.
//!
//! \return None.
//
//*****************************************************************************
static void InputSrcSet( void )
{
    typedef struct 
    {
        unsigned long ulBase;
        unsigned long ulComp;
        unsigned long ulSource;
        unsigned long ulResult;
    } Test;
    Test Sample_Test[] = { { ACMP_BASE, 0, ACMP_ASRCN_REF, 0x10 }, 
                           { ACMP_BASE, 0, ACMP_ASRCN_PIN, 0    },
                           { ACMP_BASE, 1, ACMP_ASRCN_REF, 0x10 },
                           { ACMP_BASE, 1, ACMP_ASRCN_PIN, 0    }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test);
    unsigned long ultemp = 0;
    unsigned char i = 0;
    for ( ; i < ullength; i++ )
    {
        ACMPNegativeSrcSet( Sample_Test[i].ulBase, Sample_Test[i].ulComp, 
                                                      Sample_Test[i].ulSource );
        if ( 0 == Sample_Test[i].ulComp )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR0 ) & ACMP_CR_CN;
        }
        else 
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR1 ) & ACMP_CR_CN;
        }
        TestAssert( Sample_Test[i].ulResult == ultemp ,
                                  "xacmp API \"ACMPNegativeSrcSet()\" error!" );
    }
}

//*****************************************************************************
//
//! \brief  acmp api comparator hysteresis enable and disable test.
//!
//! \return None.
//
//*****************************************************************************
static void CompHyster( void )
{
    typedef struct 
    {
        unsigned long ulBase;
        unsigned long ulComp;
        unsigned long ulResult_En;
        unsigned long ulResult_Dis;
    } Test;
    Test Sample_Test[] = { { ACMP_BASE, 0, 0x04, 0 }, 
                           { ACMP_BASE, 1, 0x04, 0 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test);
    unsigned long ultemp = 0;
    unsigned char i = 0;
    for ( ; i < ullength; i++ )
    {
        ACMPHysEnable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        if ( 0 == Sample_Test[i].ulComp )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR0 ) & ACMP_CR_HYSEN;
        }
        else 
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR1 ) & ACMP_CR_HYSEN;
        }
        TestAssert( Sample_Test[i].ulResult_En == ultemp ,
                                       "xacmp API \"ACMPHysEnable()\" error!" );
    }
    for ( i = 0; i < ullength; i++ )
    {
        ACMPHysDisable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        if ( 0 == Sample_Test[i].ulComp )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR0 ) & ACMP_CR_HYSEN;
        }
        else 
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR1 ) & ACMP_CR_HYSEN;
        }
        TestAssert( Sample_Test[i].ulResult_Dis == ultemp ,
                                      "xacmp API \"ACMPHysDisable()\" error!" ); 
    }	
}

//*****************************************************************************
//
//! \brief  acmp api comparator enable and disable test.
//!
//! \return None.
//
//*****************************************************************************
static void CompOperate( void )
{
    typedef struct 
    {
        unsigned long ulBase;
        unsigned long ulComp;
        unsigned long ulResult_En;
        unsigned long ulResult_Dis;
    } Test;
    Test Sample_Test[] = { { ACMP_BASE, 0, 0x01, 0 }, 
                           { ACMP_BASE, 1, 0x01, 0 }
    };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test);
    unsigned long ultemp = 0;
    unsigned char i = 0;
    for ( ; i < ullength; i++ )
    {
        ACMPEnable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        if ( 0 == Sample_Test[i].ulComp )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR0 ) & ACMP_CR_CMPEN;
        }
        else 
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR1 ) & ACMP_CR_CMPEN;
        }
        TestAssert( Sample_Test[i].ulResult_En == ultemp ,
                                          "xacmp API \"ACMPEnable()\" error!" );
    }
    for ( i = 0; i < ullength; i++ )
    {
        ACMPDisable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        if ( 0 == Sample_Test[i].ulComp )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR0 ) & ACMP_CR_CMPEN;
        }
        else 
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR1 ) & ACMP_CR_CMPEN;
        }
        TestAssert( Sample_Test[i].ulResult_Dis == ultemp ,
                                         "xacmp API \"ACMPDisable()\" error!" );
    }
}

//*****************************************************************************
//
//! \brief  acmp api comparator interrupt enble and disable test.
//!
//! \return None.
//
//*****************************************************************************
static void CompInt( void )
{
    typedef struct 
    {
        unsigned long ulBase;
        unsigned long ulComp;
        unsigned long ulResult_En;
        unsigned long ulResult_Dis;
    } Test;
    Test Sample_Test[] = { { ACMP_BASE, 0, 0x02, 0 }, 
                           { ACMP_BASE, 1, 0x02, 0 }
                         };
    
    unsigned int ullength = sizeof(Sample_Test) / sizeof(Test);
    unsigned long ultemp = 0;
    unsigned char i = 0;
    for ( ; i < ullength; i++ )
    {
        ACMPIntEnable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        if ( 0 == Sample_Test[i].ulComp )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR0 ) & ACMP_CR_CMPIE;
        }
        else 
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR1 ) & ACMP_CR_CMPIE;
        }
        TestAssert( Sample_Test[i].ulResult_En == ultemp ,
                                       "xacmp API \"ACMPIntEnable()\" error!" );
    }
    for ( i = 0; i < ullength; i++ )
    {
        ACMPIntDisable( Sample_Test[i].ulBase, Sample_Test[i].ulComp );
        if ( 0 == Sample_Test[i].ulComp )
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR0 ) & ACMP_CR_CMPIE;
        }
        else 
        {
            ultemp = xHWREG( Sample_Test[i].ulBase + ACMP_CR1 ) & ACMP_CR_CMPIE;
        }
        TestAssert( Sample_Test[i].ulResult_Dis == ultemp ,
                                      "xacmp API \"ACMPIntDisable()\" error!" );
    }
    
}

unsigned long user_Callback( void *pvCBData, unsigned long ulEvent,
                            unsigned long ulMsgParam, void *pvMsgData )
{
    TestEmitToken( 'T' );
    
    return 0;
}

//*****************************************************************************
//
//! \brief  xacmp api comparator interrupt init callback test.
//!
//! \return None.
//
//*****************************************************************************
static void Int_Callback( void )
{
    xACMPConfigure( xACMP0_BASE, 0, xACMP_ASRCN_REF );
    
    xACMPIntCallbackInit( xACMP0_BASE, 0, user_Callback );
    xACMPIntEnable( xACMP0_BASE, 0 );	
    xIntEnable( xINT_ACMP0 );

    xACMPEnable( xACMP0_BASE, 0 );

    TestAssertQBreak( "T", "xacmp API \"xACMPIntCallbackInit()\" error!", 0xFFFFFFFF );
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
    InputSrcSet( );       
    CompHyster( );
    CompOperate( );
    CompInt( );
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
    // acmp pin config
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

//*****************************************************************************
//
//! \brief xacmp002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xacmp002Execute( void )
{
    Int_Callback( );
}

//*****************************************************************************
//
//! \brief Get the Test description of xacmp002 register test.
//!
//! \return the desccription of the xacmp002 test.
//
//*****************************************************************************
static char* xacmp002GetTest( void )
{
    return "xacmp, 002, xacmp register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xacmp002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xacmp002Setup( void )
{
    //
    // reset acmp 
    //
    SysCtlPeripheralReset( SYSCTL_PERIPH_ACMP );
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xacmp002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xacmp002TearDown( void )
{
    
}

//
// Xacmp002 register test case struct.
//
const tTestCase sTestXacmp002Register = {
    xacmp002GetTest,		
    xacmp002Setup,
    xacmp002TearDown,
    xacmp002Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternXacmp[] =
{
    &sTestXacmp001Register,
    &sTestXacmp002Register,
    0
};
