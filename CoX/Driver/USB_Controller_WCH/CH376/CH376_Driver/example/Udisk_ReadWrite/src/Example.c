//*****************************************************************************
//
//! \file Example.c
//! \brief CH376 Read Write test example (Use software SPI)
//!  Support software SPI, hardware SPI, parallel interface
//! \version V2.2.1.0
//! \date 1/5/2013
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2013, CooCox
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions
//! are met:
//!
//!     * Redistributions of source code must retain the above copyright
//! notice, this list of conditions and the following disclaimer.
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution.
//!     * Neither the name of the <ORGANIZATION> nor the names of its
//! contributors may be used to endorse or promote products derived
//! from this software without specific prior written permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//! You may see some warnings after compile this project, don't mind.
//! Most of those warnings are caused by signed char pointer parameter pass
//! to unsigned char pointer. In this application it doesn't matter.
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xsysctl.h"
#include "stdio.h"
#include "hw_CH376INC.h"
#include "CH376.h"
#include "CH376_FS.h"

unsigned char Buff[513];


//*********************************************************************************
//
//! \brief Rename a file
//
//! \param pucOldName the old file name
//! \param pucNewName the new file name
//!
//! \return status code status code refer to hw_CH376INC.h
//
//**********************************************************************************
UINT8	RenameFileName( char *pOldName, char *pNewName )
{
    UINT8	ucDotPos, s;
    P_FAT_DIR_INFO	pDir;

    s = CH376FileOpen( pNewName );
    if(s == USB_INT_SUCCESS)
    {
        printf("There is already a file named %s\n\r rename failed\n\r", pNewName);
        return (ERR_NAME_EXIST);
    }
    s = CH376FileOpen( pOldName );  //open the original file
    if ( s == USB_INT_SUCCESS )
    {
        s = CH376DirInfoRead( );  // load current file information data(FAT_DIR_INFO) to CH376 internal buffer
        if ( s == USB_INT_SUCCESS )
        {
            CH376ReadBlock( Buff );  //read out file information data from internal buffer and store in Buff.
            pDir = (P_FAT_DIR_INFO)Buff;  //convert data format to P_FAT_DIR_INFO
            for(ucDotPos = 0; ucDotPos < 12; ucDotPos++)
            {
                if(pNewName[ucDotPos] == '.') break;
            }
            //
            // the file name in the buffer is 8+3 format for example ABCDEFGHTXT or ABCxxxxxCxx(x represents blank)
            //
            for(s = 0; s < 12; s++)
            {
                if(s < ucDotPos)
                {
                    Buff[s] = pNewName[s];
                }
                else if(s < 8)
                {
                    Buff[s] = ' ';
                }
                else if(s > 8)
                {
                    if(pNewName[ucDotPos+s-8] != 0)
                    {
                        Buff[s-1] = pNewName[ucDotPos+s-8];
                    }
                    else
                    {
                        Buff[s-1] = ' ';
                    }
                }
            }
            //
            //load current file information data(FAT_DIR_INFO) to CH376 internal buffer
            //
            s = CH376DirInfoRead( );
            if ( s == USB_INT_SUCCESS )
            {
                //
                //write renamed file name data to internal buffer where offset address is 0 and data count is 11
                //
                CH376WriteOfsBlock( &Buff, 0, 11 );
                s = CH376DirInfoSave( );  //save file information
                mStopIfError(s);
            }
        }
        CH376FileClose( FALSE );
    }
    return( s );
}

//*********************************************************************************
//
//! \brief CH376 test function
//
//! \param None
//!
//! This function will test U-disk initialization, getting disk information
//! basic read write functions and file rename. We only use short file name mode
//! more function please refer to CH376_FS.h and http://wch.cn about CH376
//! \return None
//
//**********************************************************************************

void CH376Example(void)
{
    UINT8 s;
    UINT16 usDataCnt;
    unsigned int ulFileSize, ulSetcorCnt, ulFileCursor = 0;
    xSysCtlClockSet(72000000,  xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    //
    // This dealy is essential. If the dealy is too short, CH376 can't be initialized
    //
    mDelaymS( 100 );
    //
    //initialize USART for printf() to get debug information
    //
    mInitSTDIO( );
    printf( "Start\n\r" );

    //
    // CH376 initialization
    //
    s = mInitCH376Host( );
    mStopIfError( s );

    printf( "Wait Udisk/SD\n\r" );
    //
    // waiting for U-disk plug in. MCU can check SD card socket to get state of connection
    //
    while ( CH376DiskConnect( ) != USB_INT_SUCCESS )
    {
        mDelaymS( 100 );
    }
    mDelaymS( 200 );

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
    s = CH376ReadBlock( Buff );
    if ( s == sizeof( INQUIRY_DATA ) )
    {
        //
        // get device information
        //
        Buff[ s ] = 0;
        printf( "UdiskInfo: %s\n\r", ((P_INQUIRY_DATA)Buff)->VendorIdStr);
    }
    CH376DiskCapacity(&ulSetcorCnt);
    printf("Capacity of U-disk: %dMB\n\r", ulSetcorCnt / (1048576 / DEF_SECTOR_SIZE));
    CH376DiskQuery(&ulSetcorCnt);
    printf("Available capacity: %dMB\n\r", ulSetcorCnt / (1048576 / DEF_SECTOR_SIZE));

    printf("Read file TEST.TXT from U-disk\n\r");
    //
    // attention: in 8.3 format file name mode, CH376 only support upper case file name.
    // CH376FileOpen() can only open file in root directory or current directory
    // if the file name contains one or more directory, you should use CH376FileOpenPath()
    //
    s = CH376FileOpen("/TEST.TXT");
    mStopIfError(s);
    ulFileSize = CH376GetFileSize();
    printf("File Size :%dBytes\n\r", ulFileSize);
    printf("\n\rFile contents are:\n\n\r");
    //
    // To modify macro MAX_STRING_SIZE value in file printf.c if you want to print more than 100 characters
    // or error message will be sent in the UART data
    //
    while(ulFileCursor < ulFileSize)
    {
        CH376ByteRead(Buff, 512, &usDataCnt);
        if(usDataCnt < 512) Buff[usDataCnt] = 0;
        printf("%s", Buff);
        ulFileCursor += usDataCnt;
    }
    CH376FileClose(FALSE);
    printf("\n\n\rFile read OK.\n\r");

    printf("\nWrite file TST.TXT to U-disk\n\r");
    s = CH376FileOpenPath("/CH376TST/TST.TXT");
    if ( s != USB_INT_SUCCESS )
    {
        //
        // if file path not found, firstly create the folder then create the file
        //
        printf("TST.TXT not found, trying to create this file\n\r");
        s = CH376DirCreate("/CH376TST");
        mStopIfError(s);
        //CH376FileClose(FALSE);
        s = CH376FileCreate("TST.TXT");
        mStopIfError(s);
        s = CH376ByteWrite("U-disk write test\n\rOk\n\rsafhui3324\n\r", 35, &usDataCnt);
        mStopIfError(s);
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
        CH376ByteLocate(0xFFFFFFFF);
        s = CH376ByteWrite("\n\r1.Data added:\n\r2.U-disk write test\n\r3.OK\n\r4.safhui3324\n\r", 58, &usDataCnt);
        mStopIfError(s);
        //
        // enable auto update file size
        //
        CH376FileClose(TRUE);
    }
    printf("\n\rWrite in data are:\n\r");
    CH376FileOpenPath("/CH376TST/TST.TXT");
    ulFileCursor = 0;
    ulFileSize = CH376GetFileSize();
    while(ulFileCursor < ulFileSize)
    {
        CH376ByteRead(Buff, 512, &usDataCnt);
        if(usDataCnt < 512) Buff[usDataCnt] = 0;
        printf("%s", Buff);
        ulFileCursor += usDataCnt;
    }
    CH376FileClose(FALSE);
    CH376FileOpenPath("/CH376TST");
    mStopIfError(s);
    //s=CH376FileErase("TEST.C");
    s = RenameFileName("TST.TXT", "TEST.C");
    if(s == USB_INT_SUCCESS)printf("\n\r file name rename OK!\n\r");
    printf("\n\r All test over!\n\r");
}
