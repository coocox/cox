//*****************************************************************************
//
//! @page CH376_testcase CH376 function test
//!
//! File: @ref CH376Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the CH376 sub component.<br><br>
//! - \p Board: STM32 Fire Bull board <br><br>
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
//! - \subpage test_CH376_Function
//! .
//! \file CH376Test.c
//! \brief CH376 test source file
//! \brief CH376 test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_CH376INC.h"
#include "CH376.h"
#include "CH376_FS.h"
#include "stdio.h"

#define Length 513
unsigned char ucWriteData[Length] = "U-disk write test\n\rOk\n\rsafhui3324\n\r";
unsigned char ucReadData[Length] = {0};

//*****************************************************************************
//
//! \brief Get the Test description of CH376 Function test.
//!
//! \return the desccription of the CH376 test.
//
//*****************************************************************************
static char *CH376GetTest(void)
{

    return "CH376 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of CH376 test.
//!
//! \return None.
//
//*****************************************************************************
static void CH376Setup(void)
{
    unsigned long i = 0;
    //
    // Set SysClk 72MHz using Extern 8M oscillator
    //

    //xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN|xSYSCTL_XTAL_8MHZ);
    printf("\n\r Please plug in USB disk first.\n\r");

    mDelaymS( 100 );
    //
    // Initialize CH376 as USB host
    //
    mInitCH376Host( );

    //
    // Check disk connection
    //
    while ( CH376DiskConnect( ) != USB_INT_SUCCESS )
    {
        mDelaymS( 100 );
        if(++i > 100) break;
    }
    if(i == 101)
    {
        printf("\n\rDisk connection failed!\n\r");
    }

}

//*****************************************************************************
//
//! \brief something should do after the test execute of CH376 test.
//!
//! \return None.
//
//*****************************************************************************
static void CH376TearDown(void)
{
    return;
}

//*****************************************************************************
//
//! \brief CH376 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void CH376Execute(void)
{
    unsigned char s;
    UINT16 usDataCnt;
    unsigned int ulFileSize, ulSetcorCnt;


    //waiting for USB device get ready
    for ( s = 0; s < 10; s ++ )
    {
        mDelaymS( 50 );
        printf( "Ready ?\n\r" );
        //
        // Initialize disk and check if disk is ready
        //
        if ( CH376DiskMount( ) == USB_INT_SUCCESS ) break;
    }
    s = CH376ReadBlock( ucReadData );
    TestAssert((s == sizeof( INQUIRY_DATA )), "CH376 API \"CH376ReadBlock()\"error!");
    if ( s == sizeof( INQUIRY_DATA ) )
    {
        //
        // get device information
        //
    	ucReadData[ s ] = 0;
        printf( "UdiskInfo: %s\n\r", ((P_INQUIRY_DATA)ucReadData)->VendorIdStr);
    }
    s = CH376DiskCapacity(&ulSetcorCnt);
    TestAssert((s == USB_INT_SUCCESS), "CH376 API \"CH376DiskCapacity()\"error!");
    printf("Capacity of U-disk: %dMB\n\r", ulSetcorCnt / (1048576 / DEF_SECTOR_SIZE));
    s = CH376DiskQuery(&ulSetcorCnt);
    TestAssert((s == USB_INT_SUCCESS), "CH376 API \"CH376DiskCapacity()\"error!");
    printf("Available capacity: %dMB\n\r", ulSetcorCnt / (1048576 / DEF_SECTOR_SIZE));

    s = CH376FileOpenPath("/CH376TST/TST.TXT");
    if ( s != USB_INT_SUCCESS )
    {
        //
        // if file path not found, firstly create the folder then create the file
        //
        s = CH376DirCreate("/CH376TST");
        TestAssert((s == USB_INT_SUCCESS), "CH376 API \"CH376DirCreate()\"error!");
        s = CH376FileCreate("TST.TXT");
        TestAssert((s == USB_INT_SUCCESS), "CH376 API \"CH376FileCreate()\"error!");
        s = CH376ByteWrite(ucWriteData, 35, &usDataCnt);
        TestAssert((s == USB_INT_SUCCESS), "CH376 API \"CH376ByteWrite()\"error!");
        //
        // After modifying a file, the parameter of CH376FileClose() must be TRUE to update
        // file size or you will find the file not available when you open the file on computer.
        //
        CH376FileClose(TRUE);
    }
    else
    {
        //
        // if file found, move file pointer to the end of file, then append data to the file
        //
        CH376ByteLocate(0x0);
        s = CH376ByteWrite(ucWriteData, 35, &usDataCnt);
        TestAssert((s == USB_INT_SUCCESS), "CH376 API \"CH376ByteWrite()\"error!");
        //
        // enable auto update file size
        //
        CH376FileClose(TRUE);
    }
    CH376FileOpenPath("/CH376TST/TST.TXT");
    ulFileSize = CH376GetFileSize();
    CH376ByteRead(ucReadData, 512, &usDataCnt);
    for(s = 0; s < ulFileSize; s++)
    {
        TestAssert((ucReadData[s] == ucWriteData[s]), "CH376 API \"CH376ByteRead()\"error!");
    }
    CH376FileClose(FALSE);
    printf("\n\r All test over!\n\r");

}
//
// CH376 Function test case struct.
//
const tTestCase sTestCH376Function =
{
    CH376GetTest,
    CH376Setup,
    CH376TearDown,
    CH376Execute
};

//
// CH376 test suits.
//
const tTestCase *const psPatternCH376Test[] =
{
    &sTestCH376Function,
    0
};
