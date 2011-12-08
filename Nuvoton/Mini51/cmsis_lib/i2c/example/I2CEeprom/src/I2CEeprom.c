//*****************************************************************************
//
//! \file DrvI2C.h
//! \brief Mini51 I2C Driver Sample Code with EEPROM 24LC64.
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.    
//
//*****************************************************************************

#include "DrvGPIO.h"
#include "DrvI2C.h"
#include "DrvSYS.h"

//*****************************************************************************
//
//!
//! Global variables  
//!
//
//*****************************************************************************
uint8_t Device_Addr;
uint8_t Tx_Data[3];
uint8_t Rx_Data;
uint8_t DataLen;
volatile uint8_t EndFlag = 0;

void I2C_Callback_Rx(uint32_t status);
void I2C_Callback_Tx(uint32_t status);

//*****************************************************************************
//
//!
//! Mini51 I2C Driver Sample Code with EEPROM 24LC64
//!
//
//*****************************************************************************
void  I2CEeprom(void)
{
    uint32_t u32data, i;
    
    //
    // Enable high external clock and use it as system clock (HCLK)
    //
	DrvSYS_Open(XTL_CLK);

    //
    // Waiting for 12M Xtal stable
    //
    while (DrvSYS_GetChipClockSourceStatus(XTL_CLK) != 1);

    //
    // Set I2C I/O
    //
    DrvGPIO_InitFunction(FUNC_I2C);

    //
    // Open I2C and set clock = 100Kbps
    //
    DrvI2C_Open(100000);

    //
    // Get I2C clock
    //
    u32data = DrvI2C_GetClockFreq();

    //
    // Set I2C slave addresses
    //
    DrvI2C_SetAddress(0, 0x15, 0);
    DrvI2C_SetAddress(1, 0x35, 0);
    DrvI2C_SetAddress(2, 0x55, 0);
    DrvI2C_SetAddress(3, 0x75, 0);

    //
    // Enable I2C interrupt and set corresponding NVIC bit
    //
    DrvI2C_EnableInt();

    Device_Addr = 0x50;

    for (i = 0; i < 0x100; i++)
    {
        Tx_Data[0] = (uint8_t)((i & 0xFF00) >> 8);
        Tx_Data[1] = (uint8_t)(i & 0x00FF);
        Tx_Data[2] = (uint8_t)(Tx_Data[1] + 3);

        DataLen = 0;
        EndFlag = 0;

        //
        // Install I2C call back function for write data to slave
        //
        DrvI2C_InstallCallback(I2CFUNC, I2C_Callback_Tx);

        //
        // I2C as master sends START signal
        //
        DrvI2C_Ctrl(1, 0, 0, 0);

        //
        // Wait I2C Tx Finish
        //
        while (EndFlag == 0);
        EndFlag = 0;

        //
        // Uninstall I2C call back function for write data to slave 
        //
        DrvI2C_UninstallCallBack(I2CFUNC);

        //
        // Install I2C call back function for read data from slave
        //
        DrvI2C_InstallCallback(I2CFUNC, I2C_Callback_Rx);

        DataLen = 0;
        Device_Addr = 0x50;
        DrvI2C_Ctrl(1, 0, 0, 0);

        //
        // Wait I2C Rx Finish
        //
        while (EndFlag == 0);

        //
        // Compare data
        //
        if (Rx_Data != Tx_Data[2])
        {
            return -1;
        }
    }

    //
    // Disable I2C interrupt and clear corresponding NVIC bit
    //
    DrvI2C_DisableInt();

    //
    // Close I2C
    //
    DrvI2C_Close();
}

//*****************************************************************************
//
//!
//! I2C Rx Callback Function 
//!
//
//*****************************************************************************
void I2C_Callback_Rx(uint32_t status)
{
    //
    // START has been transmitted and prepare SLA+W
    //
    if (status == 0x08)
    {
        DrvI2C_WriteData(Device_Addr<<1);
        DrvI2C_Ctrl(0, 0, 1, 0);
    }
    //
    // SLA+W has been transmitted and ACK has been received
    //
    else if (status == 0x18)
    {
        DrvI2C_WriteData(Tx_Data[DataLen++]);
        DrvI2C_Ctrl(0, 0, 1, 0);
    }
    //
    // SLA+W has been transmitted and NACK has been received 
    //
    else if (status == 0x20)
    {
        DrvI2C_Ctrl(1, 1, 1, 0);
    }
    //
    // DATA has been transmitted and ACK has been received
    //
    else if (status == 0x28)
    {
        if (DataLen != 2)
        {
            DrvI2C_WriteData(Tx_Data[DataLen++]);
            DrvI2C_Ctrl(0, 0, 1, 0);
        }
        else
        {
            DrvI2C_Ctrl(1, 0, 1, 0);
        }
    }
    //
    // Repeat START has been transmitted and prepare SLA+R 
    //
    else if (status == 0x10)
    {
        DrvI2C_WriteData(Device_Addr<<1 | 0x01);
        DrvI2C_Ctrl(0, 0, 1, 0);
    }
    //
    // SLA+R has been transmitted and ACK has been received
    //
    else if (status == 0x40)
    {
        DrvI2C_Ctrl(0, 0, 1, 0);
    }
    //
    // DATA has been received and NACK has been returned
    //
    else if (status == 0x58)
    {
        Rx_Data = DrvI2C_ReadData();
        DrvI2C_Ctrl(0, 1, 1, 0);
        EndFlag = 1;
    }
    else
    {

    }
}

//*****************************************************************************
//
//!
//! I2C Tx Callback Function 
//!
//
//*****************************************************************************
void I2C_Callback_Tx(uint32_t status)
{
    //
    // START has been transmitted 
    //
    if (status == 0x08)
    {
        DrvI2C_WriteData(Device_Addr<<1);
        DrvI2C_Ctrl(0, 0, 1, 0);
    }
    //
    // SLA+W has been transmitted and ACK has been received
    //
    else if (status == 0x18)
    {
        DrvI2C_WriteData(Tx_Data[DataLen++]);
        DrvI2C_Ctrl(0, 0, 1, 0);
    }
    //
    // SLA+W has been transmitted and NACK has been received
    //
    else if (status == 0x20)
    {

        DrvI2C_Ctrl(1, 1, 1, 0);
    }
    //
    // DATA has been transmitted and ACK has been received
    //
    else if (status == 0x28)
    {
        if (DataLen != 3)
        {
            DrvI2C_WriteData(Tx_Data[DataLen++]);
            DrvI2C_Ctrl(0, 0, 1, 0);
        }
        else
        {
            DrvI2C_Ctrl(0, 1, 1, 0);
            EndFlag = 1;
        }
    }
    else
    {

    }
}

