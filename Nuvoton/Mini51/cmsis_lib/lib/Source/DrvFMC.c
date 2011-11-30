//*****************************************************************************
//
//! \file DrvFMC.c
//! \brief Driver for the FMC.
//! \version v1.02.002
//! \date 09/05/2011
//! \author Nuvoton
//! \copy
//!
//! Copyright (c)  2011, Nuvoton 
//! All rights reserved.
//
//*****************************************************************************

//*****************************************************************************
//
//! Include related headers
//
//*****************************************************************************
#include <stdio.h>
#include "mini51.h"
#include "DrvFMC.h"

//*****************************************************************************
//
//! \brief Write data into Flash include APROM, LDROM, Data Flash, and Config. 
//!
//! \param u32addr Flash address include APROM, LDROM, Data Flash, and Config.
//!
//! \param u32data Data.
//!
//! \return 0		 Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
int32_t DrvFMC_Write(uint32_t u32addr, uint32_t u32data)
{
    FMC->ISPCMD = 0x21;
    FMC->ISPADR	= u32addr;
	FMC->ISPDAT	= u32data;
	FMC->ISPTRG_BITS.ISPGO = 1;	
	
	while (FMC->ISPTRG_BITS.ISPGO);
	
	if (FMC->ISPCON_BITS.ISPFF == 1)
	{
		FMC->ISPCON_BITS.ISPFF = 1;
		return E_DRVFMC_ERR_ISP_FAIL;
	}
	
	return 0;
}

//*****************************************************************************
//
//! \brief Read data from Flash include APROM, LDROM, Data Flash, and Config. 
//!
//! \param u32addr Flash address include APROM, LDROM, Data Flash, and Config.
//!
//! \param u32data Data.
//!
//! \return 0		 Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
int32_t DrvFMC_Read(uint32_t u32addr, uint32_t * u32data)
{ 
    FMC->ISPCMD = 0;
    FMC->ISPADR	= u32addr;
	FMC->ISPDAT	= 0;
	FMC->ISPTRG_BITS.ISPGO = 1;    
	
	while (FMC->ISPTRG_BITS.ISPGO);

	if (FMC->ISPCON_BITS.ISPFF == 1)
	{
		FMC->ISPCON_BITS.ISPFF = 1;
		return E_DRVFMC_ERR_ISP_FAIL;
	}
	
	*u32data = FMC->ISPDAT;
	return 0;
}

//*****************************************************************************
//
//! \brief Page Erase Flash include APROM, LDROM, Data Flash, and Config. 
//!  The erase unit is 512 bytes.
//!
//! \param u32addr Flash page base address or Config0 address.
//!
//! \return 0		 Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
int32_t DrvFMC_Erase(uint32_t u32addr)
{
    FMC->ISPCMD = 0x22;
    FMC->ISPADR	= u32addr;
	FMC->ISPTRG_BITS.ISPGO = 1;	
	
	while (FMC->ISPTRG_BITS.ISPGO);

	if (FMC->ISPCON_BITS.ISPFF == 1)
	{
		FMC->ISPCON_BITS.ISPFF = 1;
		return E_DRVFMC_ERR_ISP_FAIL;
	}
	
	return 0;
}

//*****************************************************************************
//
//! \brief Page Erase Flash include APROM, LDROM, Data Flash, and Config. 
//!  The erase unit is 512 bytes.
//!
//! \param u32data Data
//!
//! \return 0		 Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
int32_t DrvFMC_ReadCID(uint32_t * u32data)
{
    FMC->ISPCMD = 0xB;
	FMC->ISPADR	= 0;
    FMC->ISPTRG_BITS.ISPGO = 1;

	while (FMC->ISPTRG_BITS.ISPGO);

	if (FMC->ISPCON_BITS.ISPFF == 1)
	{
		FMC->ISPCON_BITS.ISPFF = 1;
		return E_DRVFMC_ERR_ISP_FAIL;
	} 
    
	*u32data = FMC->ISPDAT; 
    return 0;
}

//*****************************************************************************
//
//! \brief Read Device ID. 
//!
//! \param u32data Data
//!
//! \return 0		 Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
int32_t DrvFMC_ReadDID(uint32_t * u32data)
{
    FMC->ISPCMD = 0xC;
	FMC->ISPADR	= 0;
    FMC->ISPTRG_BITS.ISPGO = 1;

	while (FMC->ISPTRG_BITS.ISPGO);
    
	if (FMC->ISPCON_BITS.ISPFF == 1)
	{
		FMC->ISPCON_BITS.ISPFF = 1;
		return E_DRVFMC_ERR_ISP_FAIL;
	} 
    
	*u32data = FMC->ISPDAT; 
    return 0;
}

//*****************************************************************************
//
//! \brief Read Product ID.
//!
//! \param u32data Data
//!
//! \return 0		 Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
int32_t DrvFMC_ReadPID(uint32_t * u32data)
{
    FMC->ISPCMD = 0xC;
	FMC->ISPADR	= 0x04;
    FMC->ISPTRG_BITS.ISPGO = 1;

	while (FMC->ISPTRG_BITS.ISPGO);

	if (FMC->ISPCON_BITS.ISPFF == 1)
	{
		FMC->ISPCON_BITS.ISPFF = 1;
		return E_DRVFMC_ERR_ISP_FAIL;
	} 
    
	*u32data = FMC->ISPDAT; 
    return 0;
}

//*****************************************************************************
//
//! \brief Read Product ID.
//!
//! \param index UID index
//!
//! \param u32data Data
//!
//! \return 0		 Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
int32_t DrvFMC_ReadUID(int index, uint32_t * u32data)
{
    FMC->ISPCMD = 0x4;
	FMC->ISPADR	= 0x04 * index;
    FMC->ISPTRG_BITS.ISPGO = 1;

	while (FMC->ISPTRG_BITS.ISPGO);

	if (FMC->ISPCON_BITS.ISPFF == 1)
	{
		FMC->ISPCON_BITS.ISPFF = 1;
		return E_DRVFMC_ERR_ISP_FAIL;
	} 
    
	*u32data = FMC->ISPDAT; 
    return 0;
}

//*****************************************************************************
//
//! \brief Enable/Disable ISP function.
//!
//! \param i32Enable 1:Enable 
//!                  0:Disable
//!
//! \return 0		Success
//!        <0       Failed when illegal condition occurs  
//
//*****************************************************************************
void DrvFMC_EnableISP(void)
{
	CLK->AHBCLK_BITS.ISP_EN = 1;
	FMC->ISPCON_BITS.ISPEN = 1;
}

//*****************************************************************************
//
//! \brief Disable ISP function..
//!
//! \param None  
//!
//! \return None 
//
//*****************************************************************************
void DrvFMC_DisableISP(void)
{
	FMC->ISPCON_BITS.ISPEN = 0;
}

//*****************************************************************************
//
//! \brief Select next boot from APROM or LDROM.
//!
//! \param boot   APROM / LDROM
//!
//! \return None 
//
//*****************************************************************************
void DrvFMC_BootSelect(E_FMC_BOOTSELECT boot)
{
	FMC->ISPCON_BITS.BS = (boot)? 1: 0;
}

//*****************************************************************************
//
//! \brief To return current boot select setting.
//!
//! \param None
//!
//! \return APROM      The current boot select setting is in APROM
//!         LDROM      The current boot select setting is in LDROM 
//
//*****************************************************************************
E_FMC_BOOTSELECT DrvFMC_GetBootSelect(void)
{
	return (E_FMC_BOOTSELECT)FMC->ISPCON_BITS.BS;
}

//*****************************************************************************
//
//! \brief Enable/Disable LDROM update function.
//!
//! \param i32Enable 1:     Enable 
//!                  0:     Disable
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_EnableLDUpdate()
{	
	FMC->ISPCON_BITS.LDUEN = 1;
}

//*****************************************************************************
//
//! \brief Disable LDROM update function.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_DisableLDUpdate(void)
{	
	FMC->ISPCON_BITS.LDUEN = 0;
}

//*****************************************************************************
//
//! \brief Enable/Disable Config update function when MCU is running in APROM .
//!  or LDROM.
//!
//! \param i32Enable 1:      Enable 
//!                  0:      Disable
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_EnableConfigUpdate(void)
{	
	FMC->ISPCON_BITS.CFGUEN = 1;
}

//*****************************************************************************
//
//! \brief Disable Config update function when MCU is running in APROM or LDROM.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_DisableConfigUpdate(void)
{	
	FMC->ISPCON_BITS.CFGUEN = 0;
}

//*****************************************************************************
//
//! \brief Enable/Disable flash power saving function.
//!
//! \param i32Enable 1:      Enable 
//!                  0:      Disable
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_EnablePowerSaving(void)
{	
	FMC->FATCON_BITS.FPSEN = 1;
}

//*****************************************************************************
//
//! \brief Disable flash power saving function.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_DisablePowerSaving(void)
{	
	FMC->FATCON_BITS.FPSEN = 0;
}

//*****************************************************************************
//
//! \brief Enable flash access low speed mode. It can improve flash access 
//!  performance. when CPU runs at low speed.
//!
//! \param None
//!
//! \note Set this bit only when HCLK <= 25MHz. If HCLK > 25MHz, CPU will fetch 
//!  wrong code and cause fail result.
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_EnableLowSpeedMode(void)
{	
	FMC->FATCON_BITS.LSPEED = 1;
}

//*****************************************************************************
//
//! \brief Disable flash access low speed mode. 
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void DrvFMC_DisableLowSpeedMode(void)
{	
	FMC->FATCON_BITS.LSPEED = 0;
}

//*****************************************************************************
//
//! \brief Read Data Flash base address.
//!
//! \param None
//!
//! \return Data Flash base address
//
//*****************************************************************************
uint32_t DrvFMC_ReadDataFlashBaseAddr(void)
{	
	return FMC->DFBADR;
}

//*****************************************************************************
//
//! \brief Erase Config and write data into Config0 and Config1.
//!
//! \param u32data0 Config0 data.
//!
//! \param u32data1 Config1 data.
//!
//! \return 0		 Success
//!        <0        Failed when illegal condition occurs
//
//*****************************************************************************
int32_t DrvFMC_WriteConfig(uint32_t u32data0, uint32_t u32data1)
{		
	if (DrvFMC_Erase(CONFIG0))
		return E_DRVFMC_ERR_ISP_FAIL;
	
	if (DrvFMC_Write(CONFIG0, u32data0))
		return E_DRVFMC_ERR_ISP_FAIL;

	return DrvFMC_Write(CONFIG1, u32data1);
}

//*****************************************************************************
//
//! \brief This function is used to get the DrvFMC version number.
//!
//! \param None
//!
//! \return The DrvFMC version number.
//
//*****************************************************************************
uint32_t DrvFMC_GetVersion(void)
{
    //
	// DRVFMC_VERSION_NUM
	//
	return 1; 
}


