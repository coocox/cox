//*****************************************************************************
//
//! \file DrvI2C.h
//! \brief Defines and Macros for I2C API.
//! \version v1.02.002
//! \date 28/11/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.    
//
//*****************************************************************************
#include <stdio.h>
#include "DrvI2C.h"

#define I2C_STA              0x20
#define I2C_STO              0x10
#define I2C_SI               0x08
#define I2C_AA               0x04

static I2C_CALLBACK_T I2CHandler = {0};

//*****************************************************************************
//
//! \brief ISR to handle I2C interrupt event 
//!
//! \param None 
//!
//! \return None  
//
//*****************************************************************************
void I2C_IRQHandler(void)
{
    __IO uint32_t status;

    status  = I2C->STATUS;
	
    if (I2C->TOUT_BITS.TIF)
    {
        //
        // Clear TIF
        //
        I2C->TOUT_BITS.TIF = 1; 
        
        if (I2CHandler.TimeoutCallBackFn)
        {
            I2CHandler.TimeoutCallBackFn(status); 
        }
    }
    else
    {
        switch (status)
        {   
            //
            // Arbitration loss
            //
            case 0x38:   
            {
                if (I2CHandler.ArbitLossCallBackFn)
                    I2CHandler.ArbitLossCallBackFn(status); 
                break;
            }
            //
            // Bus error
            //
            case 0x00:     
            {
                if (I2CHandler.BusErrCallBackFn)
                    I2CHandler.BusErrCallBackFn(status); 
                break;
            }
            default:
            {
                if (I2CHandler.I2CCallBackFn)
                    I2CHandler.I2CCallBackFn(status);           
            }       
        }       
    }
}

//*****************************************************************************
//
//! \brief Set I2C control bit 
//!
//! \param start 1:Enable / 0:Disable
//!
//! \param stop 1:Enable / 0:Disable
//!
//! \param intFlag Wrtie '1' to clear this flag
//!
//! \param ack 1:Enable / 0:Disable
//!
//! \return None  
//
//*****************************************************************************
void DrvI2C_Ctrl(uint8_t start, uint8_t stop, uint8_t intFlag, uint8_t ack)
{   
    __IO uint32_t Reg = 0;

    if (start)
        Reg |= I2C_STA;
    if (stop)
        Reg |= I2C_STO;
    if (intFlag)
        Reg |= I2C_SI;
    if (ack)
        Reg |= I2C_AA;

    I2C->CON = (I2C->CON & ~0x3C) | Reg;
}

//*****************************************************************************
//
//! \brief Write Data into I2C Data register 
//!
//! \param u8data Byte Data
//!
//! \return None  
//
//*****************************************************************************
void DrvI2C_WriteData(uint8_t u8data)
{
    I2C->DATA = u8data;
}

//*****************************************************************************
//
//! \brief Read Data from I2C Data register 
//!
//! \param None 
//!
//! \return Data from I2C Data register  
//
//*****************************************************************************
uint8_t DrvI2C_ReadData(void)
{
    return I2C->DATA;
}

//*****************************************************************************
//
//! \brief Get I2C interrupt flag 
//!
//! \param None 
//!
//! \return 0 Flag is not set 
//!         1 Flag is set 
//
//*****************************************************************************
uint8_t DrvI2C_GetIntFlag(void)
{
    return I2C->CON_BITS.SI;
}

//*****************************************************************************
//
//! \brief Clear I2C interrupt flag 
//!
//! \param None 
//!
//! \return None  
//
//*****************************************************************************
void DrvI2C_ClearIntFlag(void)
{
    I2C->CON_BITS.SI = 1;
}

//*****************************************************************************
//
//! \brief Clear I2C time out flag 
//!
//! \param None 
//!
//! \return None  
//
//*****************************************************************************
void DrvI2C_ClearTimeoutFlag(void)
{
    I2C->TOUT_BITS.TIF = 1;   
}

//*****************************************************************************
//
//! \brief Get I2C status. There are 26 status codes. Please refer to data sheet
//!  in detail. 
//!
//! \param None 
//!
//! \return status  
//
//*****************************************************************************
uint32_t DrvI2C_GetStatus(void)
{
    return I2C->STATUS; 
}

//*****************************************************************************
//
//! \brief Enable I2C function and set clock divider. I2C clock = I2C source
//!  clock / (4x(divider+1)) The maximum of I2C clock is 1MHz. 
//!
//! \param u32BusClock I2C Bus Clock (Hz)
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_Open(uint32_t u32BusClock)
{
    uint32_t divider;    
 
    //
    // Compute proper divider for I2C clock
    //
    divider = (uint32_t) (((SystemCoreClock * 10)/(u32BusClock * 4) + 5) / 10 - 1); 
    
    CLK->APBCLK_BITS.I2C_EN = 1;
    GCR->IPRST_CTL2_BITS.I2C_RST = 1;
    GCR->IPRST_CTL2_BITS.I2C_RST = 0;   
    I2C->CON_BITS.ENSI = 1;
    I2C->DIV = divider;

    return 0;
}

//*****************************************************************************
//
//! \brief Disable I2C function and clock source 
//!
//! \param None 
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_Close(void)
{
    I2C->CON_BITS.ENSI = 0;
    GCR->IPRST_CTL2_BITS.I2C_RST = 1;
    GCR->IPRST_CTL2_BITS.I2C_RST = 0;
    CLK->APBCLK_BITS.I2C_EN = 0;
    
    return 0;
}

//*****************************************************************************
//
//! \brief Set clock divider. I2C clock = I2C source clock / (4x(divider+1)) The
//!  maximum of I2C clock is 1MHz. 
//!
//! \param u32BusClock I2C Bus Clock (Hz)
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_SetClockFreq(uint32_t u32BusClock)
{
    uint32_t divider;     
 
    divider = (uint32_t) (((SystemCoreClock * 10)/(u32BusClock * 4) + 5) / 10 - 1);

    I2C->DIV = divider;

    return 0;
}

//*****************************************************************************
//
//! \brief Get I2C Bus Clock 
//!
//! \param None 
//!
//! \return I2C Bus Clock  
//
//*****************************************************************************
uint32_t DrvI2C_GetClockFreq(void)
{
    uint32_t divider;

    divider = I2C->DIV;
    return ( SystemCoreClock / ((divider+1)<<2) );
}

//*****************************************************************************
//
//! \brief Enable I2C interrupt and NVIC corresponding to I2C 
//!
//! \param None 
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_EnableInt(void)
{
    I2C->CON_BITS.EI = 1;

    NVIC_SetPriority(I2C_IRQn, (1<<__NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(I2C_IRQn);

    return 0;
}

//*****************************************************************************
//
//! \brief Disable I2C interrupt and NVIC corresponding to I2C 
//!
//! \param None 
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_DisableInt(void)
{
    I2C->CON_BITS.EI = 0;

    NVIC_DisableIRQ(I2C_IRQn);

    return 0;
}

//*****************************************************************************
//
//! \brief Enable/Disable I2C 14-bit timeout counter and set div4 bit of timeout
//!  counter 
//!
//! \param i32enable 1:Enable / 0:Disable
//! \param u8div4 1:Enable / 0:Disable
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_SetTimeoutCounter(int32_t i32enable, uint8_t u8div4)
{
    I2C->TOUT_BITS.DIV4 = u8div4;
    I2C->TOUT_BITS.ENTI = i32enable;
    return 0;
}

//*****************************************************************************
//
//! \brief Set 4 7-bit slave addresses and enable General Call function 
//!
//! \param slaveNo There are 4 slave addrss. The slaveNo is 0 ~ 3.
//! \param slave_addr 7-bit data
//! \param GC_Flag 1:Enable / 0:Disable
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_SetAddress(uint8_t slaveNo, uint8_t slave_addr, uint8_t GC_Flag)
{
    switch (slaveNo)
    {
        case 0:
            I2C->SADDR0_BITS.SADDR  = slave_addr;
            I2C->SADDR0_BITS.GC    = GC_Flag;
            break;
        case 1:
            I2C->SADDR1_BITS.SADDR = slave_addr;
            I2C->SADDR1_BITS.GC   =   GC_Flag;
            break;
        case 2:
            I2C->SADDR2_BITS.SADDR = slave_addr;
            I2C->SADDR2_BITS.GC   =   GC_Flag;
            break;
        case 3:
            I2C->SADDR3_BITS.SADDR = slave_addr;
            I2C->SADDR3_BITS.GC   =   GC_Flag;
            break;
        default:
            return E_DRVI2C_ERR_ARGUMENT;
    }   

    return 0;
}

//*****************************************************************************
//
//! \brief Set 4 7-bit slave address mask. The corresponding address bit is
//!  "Don't Care". 
//!
//! \param slaveNo There are 4 slave addrss. The slaveNo is 0 ~ 3.
//! \param slaveAddrMask 7-bit data 
//!
//! \return 0 Success  
//
//*****************************************************************************
int32_t DrvI2C_SetAddressMask(uint8_t slaveNo, uint8_t slaveAddrMask)
{
    slaveAddrMask <<= 1;

    switch (slaveNo)
    {
        case 0:
            I2C->SAMASK0_BITS.SAMASK = slaveAddrMask;
            break;
        case 1:
            I2C->SAMASK1_BITS.SAMASK = slaveAddrMask;
            break;
        case 2:
            I2C->SAMASK2_BITS.SAMASK = slaveAddrMask;
            break;
        case 3:
            I2C->SAMASK3_BITS.SAMASK = slaveAddrMask;
            break;
        default:
            return E_DRVI2C_ERR_ARGUMENT;
    }   
    return 0;
}

//*****************************************************************************
//
//! \brief Install I2C call back function for I2C normal function, Arbitration
//!  loss, Bus error and Counter timeout . 
//!
//! \param Type I2CFUNC / ARBITLOSS / BUSERROR / TIMEOUT
//! \param callbackfn Call back function 
//!
//! \return 0 Success, 
//!         <0 Failed  
//
//*****************************************************************************
int32_t DrvI2C_InstallCallback(E_I2C_CALLBACK_TYPE Type, I2C_CALLBACK callbackfn)
{
    switch(Type)
    {
        case I2CFUNC:
        {
            I2CHandler.I2CCallBackFn = callbackfn;  
            break;
        }
        case ARBITLOSS:
        {
            I2CHandler.ArbitLossCallBackFn = callbackfn;  
            break;
        }
        case BUSERROR:
        {
            I2CHandler.BusErrCallBackFn = callbackfn;  
            break;
        }        
        case TIMEOUT:
        {
            I2CHandler.TimeoutCallBackFn = callbackfn;  
            break;
        }
        default:
            return E_DRVI2C_ERR_ARGUMENT;                               
    }
    
    return 0;
}

//*****************************************************************************
//
//! \brief Uninstall I2C call back function for I2C normal function, Arbitration
//!  loss, Bus error and Counter timeout . 
//!
//! \param Type I2CFUNC / ARBITLOSS / BUSERROR / TIMEOUT 
//!
//! \return 0 Success, 
//!         <0 Failed  
//
//*****************************************************************************
int32_t DrvI2C_UninstallCallBack(E_I2C_CALLBACK_TYPE Type)
{
    switch(Type)
    {
        case I2CFUNC:
        {
            I2CHandler.I2CCallBackFn = 0;  
            break;
        }
        case ARBITLOSS:
        {
            I2CHandler.ArbitLossCallBackFn = 0;  
            break;
        }
        case BUSERROR:
        {
            I2CHandler.BusErrCallBackFn = 0;  
            break;
        }        
        case TIMEOUT:
        {
            I2CHandler.TimeoutCallBackFn = 0;  
            break;
        }
        default:
            return E_DRVI2C_ERR_ARGUMENT;                               
    }                       

    return 0;
}

//*****************************************************************************
//
//! \brief This function is used to get the DrvI2C version number 
//!
//! \param None 
//!
//! \return The DrvI2C version number  
//
//*****************************************************************************
uint32_t DrvI2C_GetVersion(void)
{
    return DRVI2C_VERSION_NUM;
}

